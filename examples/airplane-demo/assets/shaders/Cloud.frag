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
    float z = (2.0 * depth - 1.0);
    float worldDepth = (2.0 * uNearPlane * uFarPlane) / (uFarPlane + uNearPlane - z * (uFarPlane - uNearPlane));

    return uNearPlane + worldDepth;
}

void main()
{

    // float depth = texture(uDepthTexture, texCoords).r;
    vec3 screen = texture(uScreenTexture, texCoords).rgb;

    // depth = linearDepth(depth); // comparison just doesnt work
    outColor = screen;

    float distanceInsideBox;
    float distanceToBox;
    if (rayHitsBox(uAreaCorner, uAreaCorner + uAreaSize, uCameraPos, rayDirection, distanceToBox, distanceInsideBox))
    {
        outColor = vec3(0);
    }
}
