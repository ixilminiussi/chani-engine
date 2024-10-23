// Request GLSL 3.3
#version 330

// Inputs from vertex shader
// Normal (in world space)
in vec3 fragNormal;
// Position (in world space)
in vec3 fragWorldPos;
// Position (in screen space)
in vec2 texCoords;

// This corresponds to the output color to the color buffer
out vec3 outColor;

// This is used for the texture sampling
uniform sampler2D uTexture;
uniform sampler2D uScreenTexture;
uniform sampler2D uDepthTexture;

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

void main()
{
    outColor = texture(uDepthTexture, texCoords).rgb;
}
