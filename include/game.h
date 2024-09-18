#if !defined(GAME_H)
#define GAME_H

#include "actor.h"
#include "audioSystem.h"
#include "inputSystem.h"
#include "rendererOGL.h"
#include "spriteComponent.h"
#include "vector2.h"
#include "window.h"

#include <vector>

class Game {
  public:
    static Game &instance() {
        static Game inst;
        return inst;
    }

    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    Game(Game &&) = delete;
    Game &operator=(Game &&) = delete;

  private:
    Game()
        : isRunning(true), isUpdatingActors(false), fps(nullptr),
          crosshair(nullptr), follow(nullptr), orbit(nullptr), path(nullptr) {}

  public:
    bool initialize();
    void load();
    void loop();
    void unload();
    void close();

    void addActor(Actor *actor);
    void removeActor(Actor *actor);
    RendererOGL &getRenderer() { return renderer; }
    AudioSystem &getAudioSystem() { return audioSystem; }

  private:
    void processInput();
    void update(float dt);
    void render();

    bool isRunning;
    Window window;
    RendererOGL renderer;
    AudioSystem audioSystem;
    InputSystem inputSystem;

    bool isUpdatingActors;
    std::vector<Actor *> actors;
    std::vector<Actor *> pendingActors;

    // Game specific
    void changeCamera(int mode);

    SoundEvent musicEvent;
    class FPSActor *fps;
    class SpriteComponent *crosshair;
    class FollowActor *follow;
    class OrbitActor *orbit;
    class SplineActor *path;
};

#endif
