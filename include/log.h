#if !defined(LOG_H)
#define LOG_H

#include <SDL_log.h>
#include <string>

enum class LogCategory
{
    Application = SDL_LOG_CATEGORY_APPLICATION,
    Assert = SDL_LOG_CATEGORY_ASSERT,
    Audio = SDL_LOG_CATEGORY_AUDIO,
    Error = SDL_LOG_CATEGORY_ERROR,
    Input = SDL_LOG_CATEGORY_INPUT,
    Render = SDL_LOG_CATEGORY_RENDER,
    System = SDL_LOG_CATEGORY_SYSTEM,
    Test = SDL_LOG_CATEGORY_TEST,
    Video = SDL_LOG_CATEGORY_VIDEO
};

class Log
{
  public:
    Log() = delete;
    Log(const Log &) = delete;
    Log &operator=(const Log &) = delete;

    static void info(const std::string &message);
    static void error(LogCategory category, const std::string &message);
};

#endif
