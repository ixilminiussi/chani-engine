#version 400

uniform mat4 uViewProj;
uniform vec3 uCameraPos;
uniform float uNearDepth;
uniform float uFarDepth;

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec3 rayDirection;
out vec2 texCoords;

void main()
{
    texCoords = aTexCoords;

    vec4 clipSpacePos = vec4(aPos, 0.0, 1.0); // In clip space

    vec4 worldPos = clipSpacePos * inverse(uViewProj);

    worldPos /= worldPos.w;

    rayDirection = worldPos.xyz - uCameraPos.xyz;

    gl_Position = vec4(aPos, 0.0, 1.0);
}
