#include "vector2.h"
#include "maths.h"

template <typename T> Vector2<T> Vector2<T>::zero()
{
    return {T(0), T(0)};
}

template <typename T> Vector2<T> Vector2<T>::unitX()
{
    return {T(1), T(0)};
}

template <typename T> Vector2<T> Vector2<T>::unitY()
{
    return {T(0), T(1)};
}

template <typename T> void Vector2<T>::set(T xP, T yP)
{
    x = xP;
    y = yP;
}

template <typename T> T Vector2<T>::lengthSq() const
{
    return x * x + y * y;
}

template <typename T> T Vector2<T>::length() const
{
    return Maths::sqrt(lengthSq());
}

template <typename T> void Vector2<T>::normalize()
{
    T len = length();
    x /= len;
    y /= len;
}

template class Vector2<float>;
template class Vector2<int>;
template class Vector2<uint>;
template class Vector2<double>;
