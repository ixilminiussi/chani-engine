#if !defined(VECTOR_2_H)
#define VECTOR_2_H

#include <type_traits>

template <typename T = float> class Vector2
{
    static_assert(std::is_arithmetic_v<T>, "Vector3 can only be instantiated with arithmetic types");

  public:
    Vector2() : x(0), y(0)
    {
    }

    Vector2(T xP, T yP) : x(xP), y(yP)
    {
    }

    Vector2(T single) : x(single), y(single)
    {
    }

    template <typename N> Vector2(Vector2<N> other) : x(T(other.x)), y(T(other.y))
    {
    }

    T x;
    T y;

    static Vector2 zero();
    static Vector2 unitX();
    static Vector2 unitY();

    void set(T xP, T yP);
    T lengthSq() const;
    T length() const;
    void normalize();

    static Vector2 normalize(const Vector2 &vec)
    {
        Vector2 temp = vec;
        temp.normalize();
        return temp;
    }

    static T dot(const Vector2 &a, const Vector2 &b)
    {
        return a.x * b.x + a.y * b.y;
    }

    static Vector2 lerp(const Vector2 &a, const Vector2 &b, T f)
    {
        return Vector2(a + f * (b - a));
    }

    Vector2 &operator+=(const Vector2 &right)
    {
        x += right.x;
        y += right.y;
        return *this;
    }

    friend Vector2 operator+(const Vector2 &left, const Vector2 &right)
    {
        return Vector2(left.x + right.x, left.y + right.y);
    }

    Vector2 &operator-=(const Vector2 &right)
    {
        x -= right.x;
        y -= right.y;
        return *this;
    }

    friend Vector2 operator-(const Vector2 &left, const Vector2 &right)
    {
        return Vector2(left.x - right.x, left.y - right.y);
    }

    Vector2 &operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    friend Vector2 operator*(const Vector2 &vec, T scalar)
    {
        return Vector2(vec.x * scalar, vec.y * scalar);
    }

    friend Vector2 operator*(T scalar, const Vector2 &vec)
    {
        return Vector2(vec.x * scalar, vec.y * scalar);
    }
};

#endif
