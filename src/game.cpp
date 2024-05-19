#include "../include/game.h"

bool Game::initialize() {
    bool isWindowInit = window.initialize();
    return isWindowInit;
}

void Game::loop() {
    while(isRunning) {
        processInput();
        update();
        render();
    }
}

void Game::close() {
    window.close();
    SDL_Quit();
}

void Game::processInput() {

}

void Game::update() {

}

void Game::render() {

}
