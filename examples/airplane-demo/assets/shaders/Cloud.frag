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

vec2 rayBoxDst(vec3 boundsMin, vec3 boundsMax, vec3 rayOrigin, vec3 rayDir)
{
    vec3 t0 = (boundsMin - rayOrigin) / rayDir;
    vec3 t1 = (boundsMax - rayOrigin) / rayDir;
    vec3 tmin = min(t0, t1);
    vec3 tmax = max(t0, t1);

    float dstA = max(max(tmin.x, tmin.y), tmin.z);
    float dstB = min(tmax.x, min(tmax.y, tmax.z));

    float dstToBox = max(0, dstA);
    float dstInsideBox = max(0, dstB - dstToBox);

    return vec2(dstToBox, dstInsideBox);
}

void main()
{
    vec2 rayBoxInfo = rayBoxDst(uAreaCorner, uAreaCorner + uAreaSize, uCameraPos, rayDirection);

    float depth = texture(uDepthTexture, texCoords).r;

    outColor = texture(uScreenTexture, texCoords).rgb;
    outColor = vec3(1.0) - outColor;
    // vec3 offsetColor = texture(uScreenTexture, texCoords - vec2(0.001)).rgb;
    // if (length(outColor - offsetColor) > 0.05)
    // {
    //     outColor = vec3(0.0);
    // }
    outColor = vec3(depth);
    outColor = abs(rayDirection);
}
