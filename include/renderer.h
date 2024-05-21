#if !defined(RENDERER_H)
#define RENDERER_H

#include <SDL2/SDL.h>
#include "rectangle.h"
#include "window.h"

class Renderer {
public:
    Renderer();
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    bool initialize(Window& window);
    void beginDraw();
    void drawRect(Rectangle& rect);
    void endDraw();
    void close();

private:
    SDL_Renderer* SDLRenderer = nullptr;
};

#endif
