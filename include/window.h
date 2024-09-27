#if !defined(WINDOW_H)
#define WINDOW_H

#include <SDL.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

class Window
{
  public:
    Window();
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    bool initialize();
    void close();

    SDL_Window *getSDLWindow() const;
    int getWidth() const;
    int getHeight() const;

  private:
    SDL_Window *SDLWindow;
    int width;
    int height;
};

#endif
