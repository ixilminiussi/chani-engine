#if !defined(SHAPES_H)
#define SHAPES_H

#include <vector3.h>

struct Cuboid
{
    Vector3<float> corner;
    Vector3<float> size;
};

inline Vector3<float> getCenter(const Cuboid &c)
{
    return Vector3<float>(c.corner.x + c.size.x / 2.0f, c.corner.y + c.size.y / 2.0f, c.corner.z + c.size.z / 2.0f);
}

#endif
