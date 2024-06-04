#include "vector2.h"

#include "maths.h"

const Vector2 Vector2::zero(0, 0);
const Vector2 Vector2::unitX(1.f, 0.f);
const Vector2 Vector2::unitY(0.f, 1.f);

void Vector2::set(float xP, float yP) {
    x = xP;
    y = yP;
}

float Vector2::lengthSq() const {
    return x*x + y*y;
}

float Vector2::length() const {
    return Maths::sqrt(lengthSq());
}

void Vector2::normalize() {
    float len = length();
    x /= len;
    y /= len;
}

Vector2 Vector2::normalize(Vector2 const& vec) {
    Vector2 temp = vec;
    temp.normalize();
    return temp;
}

float Vector2::dot(Vector2 const& a, Vector2 const& b) {
    return a.x * b.x + a.y * b.y;
}

Vector2 Vector2::lerp(Vector2 const& a, Vector2 const& b, float f) {
    return Vector2(a + f * (b - a));
}
