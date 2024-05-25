#if !defined(RENDERER_H)
#define RENDERER_H

#include <SDL2/SDL.h>
#include "rectangle.h"
#include "actor.h"
#include "vector2.h"
#include "window.h"

class Renderer {
public:
    enum class Flip {
        None = SDL_FLIP_NONE,
        Horizontal = SDL_FLIP_HORIZONTAL,
        Vertical = SDL_FLIP_VERTICAL
    };

    Renderer();
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    inline SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }

    bool initialize(Window& window);

    void beginDraw();
    void draw();
    void endDraw();

    void drawRect(const Rectangle& rect) const;
    void addSprite(class SpriteComponent* sprite);
    void removeSprite(class SpriteComponent* sprite);
    void drawSprites();
    void drawSprite(const Actor& actor, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const;

    void close();

private:
    SDL_Renderer* SDLRenderer = nullptr;
    std::vector<SpriteComponent*> sprites;
};

#endif
