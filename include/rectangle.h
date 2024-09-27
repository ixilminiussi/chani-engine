#if !defined(RECTANGLE_H)
#define RECTANGLE_H

#include <SDL_rect.h>

struct Rectangle
{
    float x;
    float y;
    float width;
    float height;

    SDL_Rect toSDLRect() const;

    friend bool operator==(const Rectangle &left, const Rectangle &right)
    {
        return left.x == right.x && left.y == right.y && left.width == right.width && left.height == right.height;
    }

    friend bool operator!=(const Rectangle &left, const Rectangle &right)
    {
        return !(left == right);
    }

    static const Rectangle nullRect;
};

#endif
