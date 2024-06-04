#if !defined(GAME_H)
#define GAME_H

#include <vector>

#include "spriteComponent.h"
#include "window.h"
#include "renderer.h"
#include "assets.h"
#include "vector2.h"
#include "actor.h"
#include "asteroid.h"

class Game {
public:
    static Game& instance() {
        static Game inst;
        return inst;
    }

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

private:
    Game() : 
        isRunning(true),
        isUpdatingActors(false)
    {}

public:
    bool initialize();
    void load();
    void loop();
    void unload();
    void close();

    void addActor(Actor* actor);
    void removeActor(Actor* actor);
    void addAsteroid(Asteroid* asteroid);
    void removeAsteroid(Asteroid* asteroid);

    Renderer& getRenderer() { return renderer; }
    std::vector<Asteroid*>& getAsteroids();

private:
    void processInput();
    void update(float dt);
    void render();

    Window window;
    bool isRunning;
    Renderer renderer;

    bool isUpdatingActors;
    std::vector<Actor*> actors;
    std::vector<Asteroid*> asteroids;
    std::vector<Actor*> pendingActors;
};

#endif
