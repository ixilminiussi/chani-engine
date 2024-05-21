#if !defined VECTOR2_H
#define VECTOR2_H

struct Vector2 {
    Vector2(): x(0), y(0) {}
    Vector2(float xP, float yP) : x(xP), y(yP) {}

    float x;
    float y;

    Vector2 operator-() const {
        return Vector2(-x,-y);
    }

    void operator+=(Vector2 const& v) {
        x += v.x;
        y += v.y;
    }

    void operator/=(float f) {
        x /= f;
        y /= f;
    }

    void operator*=(float f) {
        x *= f;
        y *= f;
    }

    void operator-=(Vector2 const& v) {
        *this += -v;
    }
};

inline Vector2 operator+(Vector2 const& v1, Vector2 const& v2) {
  Vector2 v(v1);
  v += v2;
  return v;
}

inline Vector2 operator-(Vector2 const& v1, Vector2 const& v2) {
  Vector2 v(v1);
  v -= v2;
  return v;
}

inline Vector2 operator*(Vector2 const& v1, float f) {
  Vector2 v(v1);
  v *= f;
  return v;
}

inline Vector2 operator*(float f, Vector2 const& v1) {
  return v1*f;
}

#endif
