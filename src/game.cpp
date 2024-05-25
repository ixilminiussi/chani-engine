#include "../include/game.h"
#include "../include/timer.h"
#include "../include/asteroid.h"
#include <algorithm>

bool Game::initialize() {
    bool isWindowInit = window.initialize();
    bool isRenderInit = renderer.initialize(window);

    return isWindowInit && isRenderInit;
}

void Game::load() {
    Assets::loadTexture(renderer, "../assets/Ship01.png", "ship01");
    Assets::loadTexture(renderer, "../assets/Astroid.png", "Asteroid");

    Actor* actor = new Actor();
    SpriteComponent* sprite = new SpriteComponent(actor, Assets::getTexture("ship01"));
    actor -> setPosition(Vector2{ 100, 100 });

    const int asteroidNumber = 20;
    for (int i = 0; i < asteroidNumber; i ++) {
        new Asteroid();
    }
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

void Game::render() {
    renderer.beginDraw();
    renderer.draw();
    renderer.endDraw();
}
