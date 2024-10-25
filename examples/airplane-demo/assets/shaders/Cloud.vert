#version 330

// Uniforms
uniform mat4 uViewProj;  // View-projection matrix
uniform vec3 uCameraPos; // Camera's world position

// Input attributes from the vertex buffer
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoords;

// Output to the fragment shader
out vec3 rayDirection;
out vec2 texCoords;

void main()
{
    // Pass through the texture coordinates
    texCoords = aTexCoords;

    // Convert vertex position to clip space (-1 to 1 range)
    vec4 clipSpacePos = vec4(aPos, 0.0, 1.0); // In clip space

    // Unproject the clip space position to world space
    vec4 worldPos = clipSpacePos * inverse(uViewProj);

    // Perspective divide (since we are unprojecting a position)
    worldPos /= worldPos.w;

    // Calculate the ray direction by subtracting the camera position from the world position
    rayDirection = normalize(worldPos.xyz - uCameraPos);

    // Set the final position of the vertex (projected to clip space using the view-projection matrix)
    gl_Position = vec4(aPos, 0.0, 1.0); // No need to project again, since this is a post-processing quad
}
