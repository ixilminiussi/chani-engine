// Request GLSL 3.3
#version 330

// Position (in screen space)
in vec2 texCoords;

// This corresponds to the output color to the color buffer
out vec3 outColor;

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

// Screen resolution
uniform int uScreenWidth;
uniform int uScreenHeight;

void main()
{
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

    float range = 1.0 + uPersistence * 2.0;
    float finalColor = (color1 + (color2 * uPersistence) + (color3 * uPersistence)) / range + 0.5;
    outColor = vec3(finalColor);
}
