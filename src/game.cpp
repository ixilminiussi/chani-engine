#include "game.h"

#include "log.h"
#include "enemy.h"
#include "timer.h"
#include <algorithm>

bool Game::initialize() {
    bool isWindowInit = window.initialize();
    bool isRenderInit = renderer.initialize(window);

    return isWindowInit && isRenderInit;
}

void Game::load() {
    Assets::loadTexture(renderer, "assets/Airplane.png", "Airplane");
    Assets::loadTexture(renderer, "assets/Base.png", "Base");
    Assets::loadTexture(renderer, "assets/Missile.png", "Missile");
    Assets::loadTexture(renderer, "assets/Projectile.png", "Projectile");
    Assets::loadTexture(renderer, "assets/TileBrown.png", "TileBrown");
    Assets::loadTexture(renderer, "assets/TileBrownSelected.png", "TileBrownSelected");
    Assets::loadTexture(renderer, "assets/TileGreen.png", "TileGreen");
    Assets::loadTexture(renderer, "assets/TileGreenSelected.png", "TileGreenSelected");
    Assets::loadTexture(renderer, "assets/TileGrey.png", "TileGrey");
    Assets::loadTexture(renderer, "assets/TileGreySelected.png", "TileGreySelected");
    Assets::loadTexture(renderer, "assets/TileRed.png", "TileRed");
    Assets::loadTexture(renderer, "assets/TileRedSelected.png", "TileRedSelected");
    Assets::loadTexture(renderer, "assets/TileTan.png", "TileTan");
    Assets::loadTexture(renderer, "assets/TileTanSelected.png", "TileTanSelected");
    Assets::loadTexture(renderer, "assets/Tower.png", "Tower");

    grid = new Grid();
}

void Game::loop() {
    Timer timer;
    float dt = 0;

    while(isRunning) {
        float dt = timer.computeDeltaTime() / 1000.0f;
        processInput();
        update(dt);
        render();
        timer.delayTime();
    }
}

void Game::unload() {
    while (!actors.empty()) {
        delete actors.back();
    }

    Assets::clear();
}

void Game::close() {
    renderer.close();
    window.close();
    SDL_Quit();
}

void Game::processInput() {
    // SDL Event
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
        }
    }
    // Keyboard state
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    // Escape: quit game
    if (keyboardState[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    }

    // Mouse state
    int x, y;
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT) {
        grid -> processClick(x, y);
    }

    if (keyboardState[SDL_SCANCODE_B]) {
        grid -> buildTower();
    }

    isUpdatingActors = true;
    for (Actor* actor : actors) {
        actor -> processInput(keyboardState);
    }
    isUpdatingActors = false;
}

void Game::update(float dt) {
    isUpdatingActors = true;
    for (Actor* actor : actors) {
        actor -> update(dt);
    }
    isUpdatingActors = false;

    for (Actor* pendingActor : pendingActors) {
        actors.emplace_back(pendingActor);
    }
    pendingActors.clear();

    std::vector<Actor*> deadActors;
    for (Actor* actor : actors) {
        if (actor -> getState() == Actor::ActorState::Dead) {
            deadActors.emplace_back(actor);
        }
    }

    for (Actor* deadActor : deadActors) {
        delete deadActor;
    }
}

Enemy* Game::getNearestEnemy(Vector2 const& position) {
    Enemy* best = nullptr;

    if (enemies.size() > 0) {
        best = enemies[0];
        float bestDistSq = (position - enemies[0] -> getPosition()). lengthSq();
        for (size_t i = 1; i < enemies.size(); i ++) {
            float newDistSq = (position - enemies[i] -> getPosition()).lengthSq();
            if (newDistSq < bestDistSq) {
                bestDistSq = newDistSq;
                best = enemies[i];
            }
        }
    }

    return best;
}

void Game::addActor(Actor* actor) {
    if (isUpdatingActors) {
        pendingActors.emplace_back(actor);
    } else {
        actors.emplace_back(actor);
    }
}

void Game::removeActor(Actor* actor) {
    auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
    if (iter != end(pendingActors)) {
        std::iter_swap(iter, end(pendingActors) - 1);
        pendingActors.pop_back();
    }
    iter = std::find(begin(actors), end(actors), actor);
    if (iter != end(actors)) {
        std::iter_swap(iter, end(actors) - 1);
        actors.pop_back();
    }
}

void Game::addAsteroid(Asteroid* asteroid) {
    asteroids.emplace_back(asteroid);
}

void Game::removeAsteroid(Asteroid* asteroid) {
    auto iter = std::find(begin(asteroids), end(asteroids), asteroid);
    if (iter != asteroids.end()) {
        asteroids.erase(iter);
    }
}

void Game::render() {
    renderer.beginDraw();
    renderer.draw();
    renderer.endDraw();
}
