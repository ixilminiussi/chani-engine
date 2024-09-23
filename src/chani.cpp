#include "chani.h"

#include "assets.h"
#include "log.h"
#include "timer.h"

#include <algorithm>

bool Game::initialize() {
    bool isWindowInit = window.initialize();
    bool isRendererInit = renderer.initialize(window);
    bool isAudioInit = audioSystem.initialize();
    bool isInputInit = inputSystem.initialize();

    return isWindowInit && isRendererInit && isAudioInit &&
           isInputInit; // Return bool && bool && bool ...to detect error
}

void Game::addActor(Actor *actor) {
    if (isUpdatingActors) {
        pendingActors.emplace_back(actor);
    } else {
        actors.emplace_back(actor);
    }
}

void Game::removeActor(Actor *actor) {
    // Erase actor from the two vectors
    auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
    if (iter != end(pendingActors)) {
        // Swap to end of vector and pop off (avoid erase copies)
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

void Game::loop() {
    Timer timer;
    float dt = 0;
    while (isRunning) {
        float dt = timer.computeDeltaTime() / 1000.0f;
        processInput();
        update(dt);
        render();
        timer.delayTime();
    }
}

void Game::unload() {
    // Delete actors
    // Because ~Actor calls RemoveActor, have to use a different style loop
    while (!actors.empty()) {
        delete actors.back();
    }

    // Resources
    Assets::clear();
}

void Game::close() {
    inputSystem.close();
    renderer.close();
    audioSystem.close();
    window.close();
    SDL_Quit();
}
