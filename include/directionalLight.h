#if !defined(DIRECTIONAL_LIGHT_H)
#define DIRECTIONAL_LIGHT_H

#include "vector3.h"

struct DirectionalLight
{
    Vector3<float> direction;
    Vector3<float> diffuseColor;
    Vector3<float> specColor;
};

#endif
