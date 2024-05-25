#include <SDL2/SDL_image.h>
#include <algorithm>
#include "../include/renderer.h"
#include "../include/log.h"
#include "../include/spriteComponent.h"
#include "../include/actor.h"
#include "../include/maths.h"

Renderer::Renderer() : SDLRenderer(nullptr) {}

bool Renderer::initialize(Window& window) {
    SDLRenderer = SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!SDLRenderer) {
        Log::error(LogCategory::Video, "Failed to create renderer");
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        Log::error(LogCategory::Video, "Unable to initialize SDL_image");
        return false;
    }
    return true;
}

void Renderer::beginDraw() {
    SDL_SetRenderDrawColor(SDLRenderer, 120, 120, 255, 255);
    SDL_RenderClear(SDLRenderer);
}

void Renderer::draw() {
    drawSprites();
}

void Renderer::endDraw() {
    SDL_RenderPresent(SDLRenderer);
}

void Renderer::drawSprites() {
    for (SpriteComponent* sprite : sprites) {
        sprite -> draw(*this);
    }
}

void Renderer::drawSprite(const Actor& actor, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const {
    SDL_Rect dstRect;
    Vector2 position = actor.getPosition();
    float rotation = actor.getRotation();
    float scale = actor.getScale();

    dstRect.w = static_cast<int>(tex.getWidth() * scale);
    dstRect.h = static_cast<int>(tex.getHeight() * scale);

    dstRect.x = static_cast<int>(position.x - origin.x);
    dstRect.y = static_cast<int>(position.y - origin.y);

    SDL_Rect* srcSDL = nullptr;
    if (srcRect != Rectangle::nullRect) {
        srcSDL = new SDL_Rect {
            Maths::round(srcRect.x),
            Maths::round(srcRect.y),
            Maths::round(srcRect.width),
            Maths::round(srcRect.height),
        };
    }

    SDL_RenderCopyEx(SDLRenderer, tex.toSDLTexture(), srcSDL, &dstRect, -Maths::toDegrees(rotation), nullptr, SDL_FLIP_NONE);

    delete srcSDL;
}

void Renderer::addSprite(class SpriteComponent* sprite) {
    int spriteDrawOrder = sprite -> getDrawOrder();
    
    for (auto iter = begin(sprites); iter != end(sprites); iter ++) {
        if (spriteDrawOrder < (*iter) -> getDrawOrder()) {
            sprites.insert(iter, sprite);
            break;
        } 
    }
}

void Renderer::removeSprite(class SpriteComponent* sprite) {
    auto iter = std::find(begin(sprites), end(sprites), sprite);
    sprites.erase(iter);
}

void Renderer::drawRect(const Rectangle& rect) const {
    SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 255, 255);
    SDL_Rect SDLRect = rect.toSDLRect();
    SDL_RenderFillRect(SDLRenderer, &SDLRect);
}

void Renderer::close() {
    SDL_DestroyRenderer(SDLRenderer);
}
