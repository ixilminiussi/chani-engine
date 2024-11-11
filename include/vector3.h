#if !defined(VECTOR_3_H)
#define VECTOR_3_H

#include <cmath>
#include <type_traits>

template <typename T> class Matrix4;

template <typename T = float> class Vector3
{
    static_assert(std::is_arithmetic_v<T>, "Vector3 can only be instantiated with arithmetic types");

  public:
    T x;
    T y;
    T z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f)
    {
    }

    Vector3(T single) : x(single), y(single), z(single)
    {
    }

    Vector3(T xP, T yP, T zP) : x(xP), y(yP), z(zP)
    {
    }

    template <typename N> Vector3(Vector3<N> other) : x(T(other.x)), y(T(other.y)), z(T(other.z))
    {
    }

    void set(T xP, T yP, T zP);
    T lengthSq() const;
    T length() const;
    void normalize();

    const T *getAsFloatPtr() const
    {
        return reinterpret_cast<const T *>(&x);
    }

    // Vector addition (a + b)
    friend Vector3 operator+(const Vector3 &a, const Vector3 &b)
    {
        return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    // Vector subtraction (a - b)
    friend Vector3 operator-(const Vector3 &a, const Vector3 &b)
    {
        return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    // Component-wise multiplication
    friend Vector3 operator*(const Vector3 &left, const Vector3 &right)
    {
        return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
    }

    // Scalar multiplication
    friend Vector3 operator*(const Vector3 &vec, T scalar)
    {
        return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }

    // Scalar multiplication
    friend Vector3 operator*(T scalar, const Vector3 &vec)
    {
        return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }

    // Component-wise division
    friend Vector3 operator/(const Vector3 &left, const Vector3 &right)
    {
        return Vector3(left.x / right.x, left.y / right.y, left.z / right.z);
    }

    // Scalar division
    friend Vector3 operator/(const Vector3 &vec, T scalar)
    {
        return Vector3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
    }

    // Scalar division
    friend Vector3 operator/(T scalar, const Vector3 &vec)
    {
        return Vector3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
    }

    // Scalar *=
    Vector3 &operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    // Scalar /=
    Vector3 &operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // Vector +=
    Vector3 &operator+=(const Vector3 &right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
        return *this;
    }

    // Vector -=
    Vector3 &operator-=(const Vector3 &right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
        return *this;
    }

    // Normalize the provided vector
    static Vector3 normalize(const Vector3 &vec)
    {
        Vector3 temp = vec;
        temp.normalize();
        return temp;
    }

    // Dot product between two vectors (a dot b)
    static T dot(const Vector3 &a, const Vector3 &b)
    {
        return (a.x * b.x + a.y * b.y + a.z * b.z);
    }

    // Cross product between two vectors (a cross b)
    static Vector3 cross(const Vector3 &a, const Vector3 &b)
    {
        Vector3 temp;
        temp.x = a.y * b.z - a.z * b.y;
        temp.y = a.z * b.x - a.x * b.z;
        temp.z = a.x * b.y - a.y * b.x;
        return temp;
    }

    // Lerp from A to B by f
    static Vector3 lerp(const Vector3 &a, const Vector3 &b, T f)
    {
        return Vector3(a + f * (b - a));
    }

    // Reflect V about (normalized) N
    static Vector3 reflect(const Vector3 &v, const Vector3 &n)
    {
        return v - 2.0f * Vector3::dot(v, n) * n;
    }

    static Vector3 transform(const Vector3 &vec, const Matrix4<T> &mat, T w = 1.0f);

    // Transform a Vector3 by a quaternion
    static Vector3 transform(const Vector3 &v, const class Quaternion &q);

    // This will transform the vector and renormalize the w component
    static Vector3 transformWithPerspDiv(const Vector3 &vec, const Matrix4<T> &mat, T w = 1.0f);

    static Vector3 zero();
    static Vector3 unitX();
    static Vector3 unitY();
    static Vector3 unitZ();
    static Vector3 negUnitX();
    static Vector3 negUnitY();
    static Vector3 negUnitZ();
};

#endif
