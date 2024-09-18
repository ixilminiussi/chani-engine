#if !defined(SPLINE_H)
#define SPLINE_H

#include "vector3.h"

#include <vector>

struct Spline {
    std::vector<Vector3> controlPoints;

    size_t getNbPoints() const { return controlPoints.size(); }
    Vector3 compute(size_t index, float t) const;
};

#endif
