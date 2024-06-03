#if !defined(INPUT_COMPONENT_H)
#define INPUT_COMPONENT_H

#include <SDL2/SDL_stdinc.h>
#include "moveComponent.h"

class InputComponent : public MoveComponent {
public:
    InputComponent(Actor* ownerP);
    InputComponent() = delete;
    InputComponent(InputComponent const&) = delete;
    InputComponent& operator=(InputComponent const&) = delete;

    void processInput(Uint8 const* keyState);

    void setMaxForwardSpeed(float maxForwardSpeedP);
    void setMaxAngularSpeed(float maxAngularSpeedP);
    void setForwardKey(int key);
    void setBackKey(int key);
    void setClockwiseKey(int key);
    void setCounterClockwiseKey(int key);

private:
    float maxForwardSpeed;
    float maxAngularSpeed;

    int forwardKey;
    int backKey;
    int clockwiseKey;
    int counterClockwiseKey;
};

#endif
