#include "random.h"
#include <ios>
#include <sstream>

void Random::init()
{
    std::random_device rd;
    Random::seed(rd());
}

void Random::seed(unsigned int seed)
{
    sGenerator.seed(seed);
}

float Random::getFloat()
{
    return getFloatRange(0.0f, 1.0f);
}

float Random::getFloatRange(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(sGenerator);
}

int Random::getIntRange(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(sGenerator);
}

template <typename T> Vector2<T> Random::getVector2(const Vector2<T> &min, const Vector2<T> &max)
{
    Vector2<T> r = Vector2<T>(getFloat(), getFloat());
    Vector2<T> diff = max - min;
    return min + Vector2(diff.x * r.x, diff.y * r.y);
}

std::string Random::getUUID()
{
    std::ostringstream oss;

    // UUID is 8-4-4-4-12 hex digits (32 characters + 4 dashes)
    // Example: xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx

    // Generate 8 hex digits
    for (int i = 0; i < 8; ++i)
        oss << std::hex << getIntRange(0, 15);

    oss << '-';

    // Generate 4 hex digits
    for (int i = 0; i < 4; ++i)
        oss << std::hex << getIntRange(0, 15);

    oss << '-';

    // Generate 4 hex digits
    for (int i = 0; i < 4; ++i)
        oss << std::hex << getIntRange(0, 15);

    oss << '-';

    // Generate 4 hex digits
    for (int i = 0; i < 4; ++i)
        oss << std::hex << getIntRange(0, 15);

    oss << '-';

    // Generate 12 hex digits
    for (int i = 0; i < 12; ++i)
        oss << std::hex << getIntRange(0, 15);

    return oss.str();
}

std::mt19937 Random::sGenerator;
