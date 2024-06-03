#include "../include/inputComponent.h"

#include <SDL2/SDL_scancode.h>
#include "../include/log.h"

InputComponent::InputComponent(Actor* ownerP) :
    MoveComponent(ownerP),
    maxForwardSpeed(100.0f),
    maxAngularSpeed(1.0f),
    forwardKey(SDL_SCANCODE_W),
    backKey(SDL_SCANCODE_S),
    clockwiseKey(SDL_SCANCODE_D),
    counterClockwiseKey(SDL_SCANCODE_A) {}

void InputComponent::processInput(Uint8 const* keyState) {
    float forwardSpeed = 0.f;
    if (keyState[forwardKey]) {
        forwardSpeed += maxForwardSpeed;
    }
    if (keyState[backKey]) {
        forwardSpeed -= maxForwardSpeed;
    }
    setForwardSpeed(forwardSpeed);

    float angularSpeed = 0.f;
    if (keyState[clockwiseKey]) {
        angularSpeed -= maxAngularSpeed;
    }
    if (keyState[counterClockwiseKey]) {
        angularSpeed += maxAngularSpeed;
    }
    setAngularSpeed(angularSpeed);
}

void InputComponent::setMaxForwardSpeed(float maxForwardSpeedP) {
    maxForwardSpeed = maxForwardSpeedP;
}

void InputComponent::setMaxAngularSpeed(float maxAngularSpeedP) {
    maxAngularSpeed = maxAngularSpeedP;
}

void InputComponent::setForwardKey(int key) {
    forwardKey = key;
}

void InputComponent::setBackKey(int key) {
    backKey = key;
}

void InputComponent::setClockwiseKey(int key) {
    clockwiseKey = key;
}

void InputComponent::setCounterClockwiseKey(int key) {
    counterClockwiseKey = key;
}
