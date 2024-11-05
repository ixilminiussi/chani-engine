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
// Ambient light level
uniform vec3 uAmbientLight;
// Directional Light
uniform DirectionalLight uDirLight;

float linearDepth(float depth, float near, float far)
{
    return (2.0 * near * far) / (far + near - (2.0 * depth - 1.0) * (far - near));
}

vec2 rayBoxDst(vec3 boundsMin, vec3 boundsMax, vec3 rayOrigin, vec3 rayDir)
{
    vec3 tMin = (boundsMin - rayOrigin) / rayDir;
    vec3 tMax = (boundsMax - rayOrigin) / rayDir;
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

    outColor = vec3(depth);

    depth = linearDepth(depth, 10.0, 10000.0);

    if (rayBoxInfo.x < rayBoxInfo.y && rayBoxInfo.x < depth)
    {
        outColor = vec3(1.0 - depth);
    }
}
