// Request GLSL 3.3
#version 450

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

// Perlin noise uniforms =====
// == BEGIN ==================
layout(binding = 3) uniform sampler3D uPerlinTexture[10];

struct PerlinSettings
{
    uvec3 gridSize;
    uint cellScale;
    float weight;
    float timeScale;
    uint a, b;
};

layout(std140, binding = 0) uniform perlinNoiseMetaData
{
    PerlinSettings uPerlinSettings[10];
};

layout(std140, binding = 1) uniform perlinNoiseDims
{
    ivec3 uTextureDimensions[10];
};

uniform int uNoiseCount;

// == END ====================

uniform vec3 uScale;
uniform float uFloor;
uniform float uStrength;
uniform float uTime;
uniform float uTransmittanceScale;
uniform float uDarknessThreshold;
uniform float uLightAbsorption;

// bounds of cloud area
uniform vec3 uAreaCorner;
uniform vec3 uAreaSize;
uniform vec3 uCloudColor;

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

    // sample all textures
    float density = 0.0;
    float total = 0.0;

    coords /= uScale;

    for (int i = 0; i < uNoiseCount; i++)
    {
        density += texture(uPerlinTexture[i], vec3(coords.x + uTime * uPerlinSettings[i].timeScale, coords.yz) /
                                                  vec3(uTextureDimensions[i]))
                       .r *
                   uPerlinSettings[i].weight;
        total += uPerlinSettings[i].weight;
    }

    density /= total;
    density -= uFloor;
    return (density < 0) ? 0 : density * uStrength * edgeFalloff;
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
    rayHitsBox(uAreaCorner, uAreaCorner + uAreaSize, startPoint, -uDirLight.direction, distanceToBox,
               distanceInsideBox);

    float stepSize = distanceInsideBox / 5.0f;
    float totalDensity = 0.0f;

    totalDensity = 0.0f;

    for (int i = 0; i < 5; i++)
    {
        startPoint += -uDirLight.direction * stepSize;
        totalDensity += samplePerlinNoise(startPoint) * stepSize;
    }

    return uDarknessThreshold + exp(-totalDensity * uLightAbsorption) * (1 - uDarknessThreshold);
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
        float stepSize = min(max(dot(normalizedRay, uScale) * 10.0f, 10.0f), distanceInsideBox / 10.0f);
        float currentStep = 0.0f;
        float maxStep = min(distanceInsideBox, depth - distanceToBox);

        float transmittance = 1.0f;
        float lightEnergy = 0.0f;

        while (currentStep < maxStep && transmittance > 0.01)
        {
            vec3 currentSamplingPoint = uCameraPos + (normalizedRay * (distanceToBox + currentStep));
            float density = samplePerlinNoise(currentSamplingPoint);

            if (density > 0)
            {
                float lightTransmittance = lightMarch(currentSamplingPoint);

                lightEnergy += density * stepSize * transmittance * lightTransmittance;
                transmittance *= exp(-density * stepSize * uTransmittanceScale);
            }
            currentStep += stepSize;
        }

        vec3 cloudCol = lightEnergy * uCloudColor;

        outColor = outColor * transmittance + cloudCol;
    }
}
