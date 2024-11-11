#include "vector3.h"

#include "maths.h"
#include "matrix4.h"
#include "quaternion.h"

template <typename T> void Vector3<T>::set(T xP, T yP, T zP)
{
    x = xP;
    y = yP;
    z = zP;
}

template <typename T> T Vector3<T>::lengthSq() const
{
    return (x * x + y * y + z * z);
}

template <typename T> T Vector3<T>::length() const
{
    return (Maths::sqrt(lengthSq()));
}

template <typename T> void Vector3<T>::normalize()
{
    T len = length();
    x /= len;
    y /= len;
    z /= len;
}

template <typename T> Vector3<T> Vector3<T>::transform(const Vector3 &vec, const Matrix4<T> &mat, T w)
{
    Vector3<T> retVal;
    retVal.x = vec.x * mat.mat[0][0] + vec.y * mat.mat[1][0] + vec.z * mat.mat[2][0] + w * mat.mat[3][0];
    retVal.y = vec.x * mat.mat[0][1] + vec.y * mat.mat[1][1] + vec.z * mat.mat[2][1] + w * mat.mat[3][1];
    retVal.z = vec.x * mat.mat[0][2] + vec.y * mat.mat[1][2] + vec.z * mat.mat[2][2] + w * mat.mat[3][2];
    // ignore w since we aren't returning a new value for it...
    return retVal;
}

// Transform a Vector3 by a quaternion
template <typename T> Vector3<T> Vector3<T>::transform(const Vector3 &v, const Quaternion &q)
{
    // v + 2.0*cross(q.xyz, cross(q.xyz,v) + q.w*v);
    Vector3<T> qv(q.x, q.y, q.z);
    Vector3<T> retVal = v;
    retVal += 2.0f * Vector3<T>::cross(qv, Vector3<T>::cross(qv, v) + q.w * v);
    return retVal;
}

// This will transform the vector and renormalize the w component
template <typename T> Vector3<T> Vector3<T>::transformWithPerspDiv(const Vector3 &vec, const Matrix4<T> &mat, T w)
{
    Vector3<T> retVal;
    retVal.x = vec.x * mat.mat[0][0] + vec.y * mat.mat[1][0] + vec.z * mat.mat[2][0] + w * mat.mat[3][0];
    retVal.y = vec.x * mat.mat[0][1] + vec.y * mat.mat[1][1] + vec.z * mat.mat[2][1] + w * mat.mat[3][1];
    retVal.z = vec.x * mat.mat[0][2] + vec.y * mat.mat[1][2] + vec.z * mat.mat[2][2] + w * mat.mat[3][2];
    T transformedW = vec.x * mat.mat[0][3] + vec.y * mat.mat[1][3] + vec.z * mat.mat[2][3] + w * mat.mat[3][3];
    if (!Maths::nearZero(Maths::abs(transformedW)))
    {
        transformedW = 1.0f / transformedW;
        retVal *= transformedW;
    }
    return retVal;
}

template <typename T> Vector3<T> Vector3<T>::zero()
{
    return {T(0), T(0), T(0)};
}
template <typename T> Vector3<T> Vector3<T>::unitX()
{
    return {T(1), T(0), T(0)};
}
template <typename T> Vector3<T> Vector3<T>::unitY()
{
    return {T(0), T(1), T(0)};
}
template <typename T> Vector3<T> Vector3<T>::unitZ()
{
    return {T(0), T(0), T(1)};
}
template <typename T> Vector3<T> Vector3<T>::negUnitX()
{
    return {T(-1), T(0), T(0)};
}
template <typename T> Vector3<T> Vector3<T>::negUnitY()
{
    return {T(0), T(-1), T(0)};
}
template <typename T> Vector3<T> Vector3<T>::negUnitZ()
{
    return {T(0), T(0), T(-1)};
}

template class Vector3<float>;
template class Vector3<int>;
template class Vector3<double>;
template class Vector3<uint>;
