#version 400

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
uniform int uTexture1Width;
uniform int uTexture1Height;

// Second PerlinNoise
uniform sampler3D uPerlinNoise2;
// Perlin texture resolution
uniform int uTexture2Width;
uniform int uTexture2Height;

// Third PerlinNoise
uniform sampler3D uPerlinNoise3;
// Perlin texture resolution
uniform int uTexture3Width;
uniform int uTexture3Height;

// shift
uniform vec3 uShift;
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
    float timeShift = uTime;
    vec3 relativeCoords = vec3(float(uScreenWidth) * (coords.x + timeShift) / float(uTexture1Width),
                               float(uScreenHeight) * coords.y / float(uTexture1Height),
                               float(uScreenWidth) * coords.z / float(uTexture1Width));
    float color1 = texture(uPerlinNoise1, relativeCoords).r - 0.5;

    timeShift = uTime * 1.1;
    relativeCoords = vec3(float(uScreenWidth) * (coords.x + timeShift) / float(uTexture2Width),
                          float(uScreenHeight) * coords.y / float(uTexture2Height),
                          float(uScreenWidth) * coords.z / float(uTexture2Width));
    float color2 = texture(uPerlinNoise2, relativeCoords).r - 0.5;

    timeShift = uTime * .1;
    relativeCoords = vec3(float(uScreenWidth) * (coords.x + timeShift) / float(uTexture2Width),
                          float(uScreenHeight) * coords.y / float(uTexture2Height),
                          float(uScreenWidth) * coords.z / float(uTexture2Width));
    float color3 = texture(uPerlinNoise3, relativeCoords).r - 0.5;

    float range = 1.0 + uPersistence * 2.0;
    return (color1 + (color2 * uPersistence) + (color3 * uPersistence)) / range + 0.5;
}

bool rayIntersectsBox(vec3 rayOrigin, vec3 rayDir, vec3 boxMin, vec3 boxMax, out float distanceToBox,
                      out float distanceInsideBox)
{
    vec3 t0 = (boxMin - rayOrigin) / rayDir;
    vec3 t1 = (boxMax - rayOrigin) / rayDir;

    vec3 tMin = min(t0, t1);
    vec3 tMax = max(t0, t1);

    float tNear = max(max(tMin.x, tMin.y), tMin.z);
    float tFar = min(min(tMax.x, tMax.y), tMax.z);

    if (tNear > tFar || tFar < 0.0)
    {
        distanceToBox = -1.0;
        return false;
    }

    float ratio = remap(tNear, 0, uFarPlane, 1.65, 0.95); // this is stupid, but it works, let's move on

    distanceToBox = max(0.0, tNear) * ratio;
    distanceInsideBox = (max(0.0, tFar) - distanceToBox) * ratio;
    return true;
}

float linearDepth(float depth)
{
    float z_ndc = depth * 2.0 - 1.0; // Convert [0, 1] depth to [-1, 1] clip space
    float linearDepth = (2.0 * uNearPlane * uFarPlane) / (uFarPlane + uNearPlane - z_ndc * (uFarPlane - uNearPlane));
    return linearDepth - uNearPlane;
}

void main()
{
    vec3 normalizedRay = normalize(rayDirection);

    float depth = texture(uDepthTexture, texCoords).r;
    vec3 screen = texture(uScreenTexture, texCoords).rgb;

    depth = linearDepth(depth);

    outColor = screen;

    float distanceToBox;
    float distanceInsideBox;
    if (rayIntersectsBox(uCameraPos, normalizedRay, uAreaCorner, uAreaCorner + uAreaSize, distanceToBox,
                         distanceInsideBox))
    {
        if (distanceToBox < depth)
        {
            outColor = vec3(distanceToBox / uFarPlane);
        }
    }
}
