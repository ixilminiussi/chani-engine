// Request GLSL 3.3
#version 330

// Inputs from vertex shader
// Position (in world space)
in vec3 rayDirection;
// Position (in screen space)
in vec2 texCoords;
// This corresponds to the output color to the color buffer
out vec3 outColor;

// This is used for the texture sampling
uniform sampler2D uScreenTexture;
uniform sampler2D uDepthTexture;

// First PerlinNoise
uniform sampler3D uPerlinNoise1;
// Perlin texture resolution
uniform vec3 uTexture1Dimensions;

// Second PerlinNoise
uniform sampler3D uPerlinNoise2;
// Perlin texture resolution
uniform vec3 uTexture2Dimensions;

// Third PerlinNoise
uniform sampler3D uPerlinNoise3;
// Perlin texture resolution
uniform vec3 uTexture3Dimensions;

// Fourth PerlinNoise
uniform sampler3D uPerlinNoise4;
// Perlin texture resolution
uniform vec3 uTexture4Dimensions;

uniform float uScale;
uniform float uFloor;
uniform float uStrength;
uniform float uPersistence;
uniform float uTime;

// bounds of cloud area
uniform vec3 uAreaCorner;
uniform vec3 uAreaSize;

// Create a struct for directional light
struct DirectionalLight
{
    // Direction of light
    vec3 direction;
    // Diffuse color
    vec3 diffuseColor;
    // Specular color
    vec3 specColor;
};

// Uniforms for lighting
// Camera position (in world space)
uniform vec3 uCameraPos;
// View-projection matrix
uniform mat4 uViewProj;
// Near and Far planes (in world space)
uniform float uNearPlane;
uniform float uFarPlane;
uniform float uFOV;

// Screen resolution
uniform int uScreenWidth;
uniform int uScreenHeight;
// Ambient light level
uniform vec3 uAmbientLight;
// Directional Light
uniform DirectionalLight uDirLight;

float remap(float v, float minOld, float maxOld, float minNew, float maxNew)
{
    return minNew + (v - minOld) * (maxNew - minNew) / (maxOld - minOld);
}

float remap01(float v, float low, float high)
{
    return (v - low) / (high - low);
}

float samplePerlinNoise(vec3 coords)
{
    // edge falloff
    vec3 distance1 = abs(coords - uAreaCorner);
    vec3 distance2 = abs(coords - (uAreaCorner + uAreaSize));

    float smallestDistance =
        min(min(min(distance1.x, distance2.x), min(distance1.y, distance2.y)), min(distance1.z, distance2.z));
    float edgeFalloff = (smallestDistance < 100.0f) ? remap01(smallestDistance, 0.0f, 100.0f) : 1.0f;

    coords /= uScale;
    float[4] color;

    color[0] = texture(uPerlinNoise1, vec3(coords.x + uTime * 0.5f, coords.yz) / uTexture1Dimensions).r;
    color[1] = texture(uPerlinNoise2, vec3(coords.x + uTime * 1.0f, coords.yz) / uTexture2Dimensions).r;
    color[2] = texture(uPerlinNoise3, vec3(coords.x + uTime * 1.2f, coords.yz) / uTexture3Dimensions).r;
    color[3] = texture(uPerlinNoise4, vec3(coords.x + uTime * 2.0f, coords.yz) / uTexture4Dimensions).r;

    float range = 1.0f;
    float total = 1.0f;
    float combined = 0.0f;
    float persistence = 1.0f;

    for (int i = 0; i < 4; i++)
    {
        total += persistence;
        combined += color[i] * persistence;
        persistence *= uPersistence;
    }

    combined /= total;
    combined -= uFloor;
    return (combined < 0) ? 0 : combined * uStrength * edgeFalloff;
}

bool rayHitsBox(vec3 boundsMin, vec3 boundsMax, vec3 rayOrigin, vec3 rayDir, out float distanceToBox,
                out float distanceInsideBox)
{
    vec3 t0 = (boundsMin - rayOrigin) / rayDir;
    vec3 t1 = (boundsMax - rayOrigin) / rayDir;
    vec3 tmin = min(t0, t1);
    vec3 tmax = max(t0, t1);

    float dstA = max(max(tmin.x, tmin.y), tmin.z);
    float dstB = min(tmax.x, min(tmax.y, tmax.z));
    if (dstB < dstA)
        return false;

    distanceToBox = max(0, dstA);
    distanceInsideBox = max(0, dstB) - distanceToBox;

    return true;
}

float linearDepth(float depth)
{
    float z = (2.0f * depth - 1.0f);
    float worldDepth = (2.0f * uNearPlane * uFarPlane) / (uFarPlane + uNearPlane - z * (uFarPlane - uNearPlane));

    return uNearPlane + worldDepth;
}

vec3 applyRGB(vec3 new, vec3 old, float alpha)
{
    return alpha * new + (1.0f - alpha) * old;
}

float lightMarch(vec3 startPoint)
{
    float distanceInsideBox;
    float distanceToBox;
    rayHitsBox(uAreaCorner, uAreaCorner + uAreaSize, startPoint, uDirLight.direction, distanceToBox, distanceInsideBox);

    float stepSize = distanceInsideBox / 5.0f;
    float totalDensity = 0.0f;
    vec3 currentSamplingPoint = startPoint + (uDirLight.direction * stepSize);

    totalDensity = 0.0f;

    for (int i = 0; i < 4; i++)
    {
        totalDensity += samplePerlinNoise(currentSamplingPoint) * stepSize;
        currentSamplingPoint += uDirLight.direction * stepSize;
    }

    return exp(-totalDensity);
}

void main()
{
    float depth = texture(uDepthTexture, texCoords).r;
    vec3 screen = texture(uScreenTexture, texCoords).rgb;

    depth = linearDepth(depth); // comparison just doesnt work
    outColor = screen;

    vec3 normalizedRay = normalize(rayDirection);

    float distanceInsideBox;
    float distanceToBox;
    if (rayHitsBox(uAreaCorner, uAreaCorner + uAreaSize, uCameraPos, normalizedRay, distanceToBox, distanceInsideBox))
    {
        float stepSize = distanceInsideBox / 10.0f;
        float currentStep = 0.0f;
        float maxStep = min(distanceInsideBox, depth - distanceToBox);

        float transmittance = 1.0f;
        float lightEnergy = 0.0f;

        while (currentStep < maxStep)
        {
            vec3 currentSamplingPoint = uCameraPos + (normalizedRay * (distanceToBox + currentStep));
            float density = samplePerlinNoise(currentSamplingPoint);

            if (density > 0)
            {
                float lightTransmittance = lightMarch(currentSamplingPoint);

                lightEnergy += density * stepSize * transmittance * lightTransmittance;
                transmittance *= exp(-density * stepSize * 2.0f);

                if (transmittance < 0.01)
                {
                    break;
                }
            }
            currentStep += stepSize;
        }

        vec3 cloudCol = lightEnergy * vec3(1.0);

        outColor = outColor * transmittance + cloudCol;
    }
}
