#include "orbitActor.h"
#include "SDL_scancode.h"
#include <inputSystem.h>
#include <orbitCameraComponent.h>

OrbitActor::OrbitActor() : Actor(), orbitCameraComponent(nullptr), targetActor(nullptr), prevMousePosition(0.0f, 0.0f)
{
    orbitCameraComponent = new OrbitCameraComponent(this);
}

void OrbitActor::actorInput(const InputState &inputState)
{
    Vector2 relativeMousePosition = inputState.mouse.getPosition() - prevMousePosition;
    float x = relativeMousePosition.x;
    float y = relativeMousePosition.y;

    if (inputState.mouse.getButtonState(1) == ButtonState::Held)
    {
        const float maxMouseSpeed = 200.0f;
        const float maxOrbitSpeed = Maths::pi * 8;

        float yawSpeed = 0.0f;
        if (!Maths::nearZero(x))
        {
            yawSpeed = x / maxMouseSpeed;
            yawSpeed *= maxOrbitSpeed;
        }
        orbitCameraComponent->setYawSpeed(yawSpeed);

        float pitchSpeed = 0.0f;
        if (!Maths::nearZero(y))
        {
            pitchSpeed = y / maxMouseSpeed;
            pitchSpeed *= maxOrbitSpeed;
        }
        orbitCameraComponent->setPitchSpeed(pitchSpeed);
    }

    if (inputState.keyboard.getKeyState(SDL_SCANCODE_LSHIFT) != ButtonState::Held &&
        inputState.keyboard.getKeyState(SDL_SCANCODE_LCTRL) != ButtonState::Held)
    {
        orbitCameraComponent->zoom((float)inputState.mouse.getScrollWheel().y * 100.0f);
    }

    prevMousePosition += relativeMousePosition;
}

void OrbitActor::snapToActor(Actor *actor)
{
    targetActor = actor;
}

void OrbitActor::updateActor(float dt)
{
    if (targetActor != nullptr)
    {
        setPosition(Vector3<float>::lerp(getPosition(), targetActor->getPosition(), 0.2f));
    }
}
