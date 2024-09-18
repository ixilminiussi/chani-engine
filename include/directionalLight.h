#if !defined(DIRECTIONAL_LIGHT_H)
#define DIRECTIONAL_LIGHT_H

#include "vector3.h"

struct DirectionalLight {
    Vector3 direction;
    Vector3 diffuseColor;
    Vector3 specColor;
};

#endif
