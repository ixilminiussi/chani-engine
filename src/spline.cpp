#include "spline.h"

size_t Spline::getNbPoints() const
{
    return controlPoints.size();
}
Vector3<float> Spline::compute(size_t index, float t) const
{
    if (index >= controlPoints.size())
    {
        return controlPoints.back();
    }
    else if (index == 0)
    {
        return controlPoints[index];
    }
    else if (index + 2 >= controlPoints.size())
    {
        return controlPoints[index];
    }

    Vector3<float> p0 = controlPoints[index - 1];
    Vector3<float> p1 = controlPoints[index];
    Vector3<float> p2 = controlPoints[index + 1];
    Vector3<float> p3 = controlPoints[index + 2];
    // Compute position according to Catmull-Rom equation
    Vector3<float> position =
        0.5f * ((2.0f * p1) + (-1.0f * p0 + p2) * t + (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t * t +
                (-1.0f * p0 + 3.0f * p1 - 3.0f * p2 + p3) * t * t * t);
    return position;
}
