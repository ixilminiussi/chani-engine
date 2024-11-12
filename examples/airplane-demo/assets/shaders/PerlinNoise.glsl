// Request GLSL 4.3
#version 430 core

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(std430, binding = 0) readonly buffer members_in
{
    uvec4 position[];
};

layout(r32f, binding = 1) writeonly uniform image3D members_out;

uniform uint uCellScale;
uniform uvec3 uGridSize;

int sqr(int x)
{
    return x * x;
}

float sqr(float x)
{
    return x * x;
}

ivec3 toCoord(int i, ivec3 ref)
{
    int slice = (ref.x * ref.y);

    ivec3 c = ivec3(0);
    c.z = i / slice;
    c.y = (i - (c.z * slice)) / ref.x;
    c.x = (i - (c.z * slice) - (c.y * ref.x));

    return c;
}

uint toIndex(uvec3 c, uvec3 ref)
{
    return c.z * ref.x * ref.y + c.y * ref.x + c.x;
}

uvec3 wrapCoord(ivec3 c, ivec3 ref)
{
    c.x = (c.x + int(ref.x)) % int(ref.x);
    c.y = (c.y + int(ref.y)) % int(ref.y);
    c.z = (c.z + int(ref.z)) % int(ref.z);

    return uvec3(c);
}

int distanceSqr(ivec3 a, ivec3 b)
{
    ivec3 diff = abs(a - b);
    return sqr(diff.x) + sqr(diff.y) + sqr(diff.z);
}

void main()
{
    uvec3 globalID = gl_GlobalInvocationID;
    uvec3 gridID = globalID.xyz / uCellScale;

    int maxDistance = int(uCellScale * (3 * uCellScale));
    int bestDistance = maxDistance;

    float outValue;

    for (int z = int(gridID.z) - 1; z <= int(gridID.z) + 1; z++)
    {
        for (int y = int(gridID.y) - 1; y <= int(gridID.y) + 1; y++)
        {
            for (int x = int(gridID.x) - 1; x <= int(gridID.x) + 1; x++)
            {
                uvec3 cGridID = wrapCoord(ivec3(x, y, z), ivec3(uGridSize));

                ivec3 cPosition = ivec3(position[toIndex(cGridID, uGridSize)].xyz) + ivec3(x, y, z) * int(uCellScale);
                int cDistance = distanceSqr(ivec3(globalID), cPosition);
                if (cDistance < bestDistance)
                {
                    bestDistance = cDistance;
                }
            }
        }
    }

    outValue = float(bestDistance) / float(maxDistance);

    imageStore(members_out, ivec3(globalID), vec4(1.0 - outValue));
}
