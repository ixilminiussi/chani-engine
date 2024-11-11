#if !defined(SPLINE_H)
#define SPLINE_H

#include "vector3.h"

#include <vector>

struct Spline
{
    std::vector<Vector3<float>> controlPoints;

    size_t getNbPoints() const;
    Vector3<float> compute(size_t index, float t) const;
};

#endif
