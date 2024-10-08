#include "window.h"

#include "log.h"

Window::Window() : SDLWindow(nullptr), width(WINDOW_WIDTH), height(WINDOW_HEIGHT)
{
}

bool Window::initialize()
{
    int sdlInitResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD);
    if (sdlInitResult != 0)
    {
        Log::error(LogCategory::Video, "Unable to initialize SDL");
        return false;
    }

    SDLWindow = SDL_CreateWindow("Cameras", width, height, SDL_WINDOW_OPENGL);
    if (!SDLWindow)
    {
        Log::error(LogCategory::System, "Failed to create window");
        return false;
    }
    return true;
}

void Window::close()
{
    SDL_DestroyWindow(SDLWindow);
}

SDL_Window *Window::getSDLWindow() const
{
    return SDLWindow;
}

int Window::getWidth() const
{
    return height;
}

int Window::getHeight() const
{
    return height;
}
