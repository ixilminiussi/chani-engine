#include "../include/window.h"
#include "../include/log.h"

Window::Window() : SDLWindow(nullptr), width(WINDOW_WIDTH), height(WINDOW_HEIGHT) {}

bool Window::initialize() {
    int sdlInitResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlInitResult != 0) {
        Log::error(LogCategory::System, "Failed to create window");
        return false;
    }

    SDLWindow = SDL_CreateWindow("Wall Pong", 100, 100, width, height, 0);
    if (!SDLWindow) {
        Log::error(LogCategory::System, "Failed to create window");
        return false;
    }

    return true;
}

void Window::close() {
    SDL_DestroyWindow(SDLWindow);
}
