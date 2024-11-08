// Request GLSL 4.3
#version 430 core

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(std430, binding = 0) readonly buffer members_in
{
    vec3 position[];
};

layout(r32f, binding = 1) writeonly uniform image3D members_out;

uniform vec3 uCellSize;

float sqr(float x)
{
    return x * x;
}

void main()
{
    uvec3 globalID = gl_GlobalInvocationID;

    float maxDistance = sqr(uCellSize.x) + sqr(uCellSize.y);
    float bestDistance = maxDistance;

    float outValue;

    for (int i = 0; i < position.length(); i++)
    {
        float distance = (sqr(position[i].x - globalID.x)) + (sqr(position[i].y - globalID.y));

        if (distance < bestDistance)
        {
            bestDistance = distance;
        }
    }

    outValue = bestDistance / maxDistance;

    imageStore(members_out, ivec3(globalID), vec4(outValue));
}
