#if !defined VECTOR2_H
#define VECTOR2_H

struct Vector2 {
    Vector2() : x(0), y(0) {}
    Vector2(float xP, float yP) : x(xP), y(yP) {}

    float x;
    float y;
    static const Vector2 zero;
    static const Vector2 unitX;
    static const Vector2 unitY;

    void set(float xP, float yP);
    float lengthSq() const;
    float length() const;
    void normalize();

    static Vector2 normalize(Vector2 const& vec);
    static float dot(Vector2 const& a, Vector2 const& b);
    static Vector2 lerp(Vector2 const& a, Vector2 const& b, float f);

    Vector2 operator-() const {
        return Vector2(-x,-y);
    }

    Vector2& operator+=(Vector2 const& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2& operator/=(float f) {
        x /= f;
        y /= f;
        return *this;
    }

    Vector2& operator*=(float f) {
        x *= f;
        y *= f;
        return *this;
    }

    Vector2& operator-=(Vector2 const& v) {
        *this += -v;
        return *this;
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
