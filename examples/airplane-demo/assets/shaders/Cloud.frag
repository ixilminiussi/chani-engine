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
// Near and Far planes (in world space)
uniform float uNearPlane;
uniform float uFarPlane;
// Screen resolution
uniform int uScreenWidth;
uniform int uScreenHeight;
// Ambient light level
uniform vec3 uAmbientLight;
// Directional Light
uniform DirectionalLight uDirLight;

float linearDepth(float depth, float near, float far)
{
    return (2.0f * near * far) / (far + near - (2.0f * depth - 1.0f) * (far - near));
}

vec2 rayBoxDst(vec3 boundsMin, vec3 boundsMax, vec3 rayOrigin, vec3 rayDir)
{
    vec3 tMin = (boundsMin - rayOrigin) / (rayDir + vec3(1e-5));
    vec3 tMax = (boundsMax - rayOrigin) / (rayDir + vec3(1e-5));
    vec3 t1 = min(tMin, tMax);
    vec3 t2 = max(tMin, tMax);
    float tNear = max(max(t1.x, t1.y), t1.z);
    float tFar = min(min(t2.x, t2.y), t2.z);
    return vec2(tNear, tFar);
}

void main()
{
    vec2 rayBoxInfo = rayBoxDst(uAreaCorner, uAreaCorner + uAreaSize, uCameraPos, rayDirection);

    float depth = texture(uDepthTexture, texCoords).r;

    depth = linearDepth(depth, uNearPlane, uFarPlane);

    outColor = texture(uScreenTexture, texCoords).rgb;

    if (rayBoxInfo.x < rayBoxInfo.y && rayBoxInfo.x < depth)
    {
        outColor = vec3(0.0);
    }

    float timeShift = uTime;
    vec3 relativeCoords = vec3(float(uScreenWidth) * (texCoords.x + uShift.x + timeShift) / float(uTexture1Width),
                               float(uScreenHeight) * (texCoords.y + uShift.y) / float(uTexture1Height),
                               float(uScreenWidth) * uShift.z / float(uTexture1Width));
    float color1 = texture(uPerlinNoise1, relativeCoords).r - 0.5;

    timeShift = uTime * 1.1;
    relativeCoords = vec3(float(uScreenWidth) * (texCoords.x + uShift.x + timeShift) / float(uTexture2Width),
                          float(uScreenHeight) * (texCoords.y + uShift.y) / float(uTexture2Height),
                          float(uScreenWidth) * uShift.z / float(uTexture2Width));
    float color2 = texture(uPerlinNoise2, relativeCoords).r - 0.5;

    timeShift = uTime * .1;
    relativeCoords = vec3(float(uScreenWidth) * (texCoords.x + uShift.x + timeShift) / float(uTexture2Width),
                          float(uScreenHeight) * (texCoords.y + uShift.y) / float(uTexture2Height),
                          float(uScreenWidth) * uShift.z / float(uTexture2Width));
    float color3 = texture(uPerlinNoise3, relativeCoords).r - 0.5;

    float range = 1.6;
    float finalColor = (color1 + (color2 * 0.30) + (color3 * 0.30)) / range + 0.5;
    outColor = vec3(finalColor);
}
