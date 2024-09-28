#if !defined(CHANI_H)
#define CHANI_H

#include "actor.h"
#include "audioSystem.h"
#include "inputSystem.h"
#include "rendererOGL.h"
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
  Game() : isRunning(true), isUpdatingActors(false) {}

public:
  bool initialize();
  void load();
  void loop();
  void unload();
  void close();

  void addActor(Actor *actor);
  void removeActor(Actor *actor);
  RendererOGL &getRenderer();
  AudioSystem &getAudioSystem();

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
};

#endif
