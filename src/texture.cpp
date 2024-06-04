#include "texture.h"

#include "log.h"
#include <SDL2/SDL_image.h>

Texture::Texture() :
    filename(""),
    width(0),
    height(0),
    SDLTexture(nullptr) {

}

Texture::~Texture() {

}

void Texture::unload() {
    if (SDLTexture) {
        SDL_DestroyTexture(SDLTexture);
    }
}

bool Texture::load(Renderer& renderer, const string& filenameP) {
    filename = filenameP;

    SDL_Surface* surf = IMG_Load(filename.c_str());
    if (!surf) {
        Log::error(LogCategory::Application, "Failed to load texture file " + filename);
        return false;
    }
    width = surf -> w;
    height = surf -> h;

    SDLTexture = SDL_CreateTextureFromSurface(renderer.toSDLRenderer(), surf);
    SDL_FreeSurface(surf);
    if (!SDLTexture) {
        Log::error(LogCategory::Render, "Failed to convert surface to texture for " + filename);
        return false;
    }
    
    Log::info("Loaded texture " + filename);

    return true;
}

void Texture::updateInfo(int& widthOut, int& heightOut) {
    widthOut = width;
    heightOut = height;
}
