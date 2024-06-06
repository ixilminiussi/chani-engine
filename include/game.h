#if !defined(GAME_H)
#define GAME_H

#include <vector>

#include "spriteComponent.h"
#include "asteroid.h"
#include "enemy.h"
#include "actor.h"
#include "window.h"
#include "renderer.h"
#include "assets.h"
#include "vector2.h"
#include "grid.h"

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
        isUpdatingActors(false),
        grid(nullptr),
        nextEnemyTimer(0.f)
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
    Grid& getGrid() { return *grid; }
    std::vector<Enemy*>& getEnemies() { return enemies; }
    std::vector<Asteroid*>& getAsteroids() { return asteroids; }
    Enemy* getNearestEnemy(Vector2 const& position);

private:
    void processInput();
    void update(float dt);
    void render();

    Window window;
    bool isRunning;
    Renderer renderer;
    Grid* grid;
    std::vector<class Enemy*> enemies;
    float nextEnemyTimer;

    bool isUpdatingActors;
    std::vector<Actor*> actors;
    std::vector<Actor*> pendingActors;
    std::vector<Asteroid*> asteroids;
};

#endif
