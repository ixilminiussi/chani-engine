#include "rectangle.h"

const Rectangle Rectangle::nullRect{0.f, 0.f, 0.f, 0.f};

SDL_Rect Rectangle::toSDLRect() const
{
    return SDL_Rect{static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height)};
}
