#if !defined(RANDOM_H)
#define RANDOM_H

#include <random>
#include "vector2.h"

class Random {
public:
    static void init();

    static void seed(unsigned int seed);

    static float getFloat();

    static float getFloatRange(float min, float max);

    static int getIntRange(int min, int max);

    static Vector2 getVector(const Vector2& min, const Vector2& max);

private:
    static std::mt19937 sGenerator;
};

#endif 
