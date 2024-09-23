#include "racingCarActor.h"

#include <assets.h>
#include <inputSystem.h>

RacingCarActor::RacingCarActor()
    : Actor(), moveComponent(nullptr), followCameraComponent(nullptr),
      meshComponent(nullptr) {
    meshComponent = new MeshComponent(this);
    meshComponent->setMesh(Assets::getMesh("Mesh_RacingCar"));
    meshComponent->setMaterial(Assets::getMaterial("Mat_RacingCar"));
    setPosition(Vector3(0.0f, 0.0f, -100.0f));

    moveComponent = new MoveComponent(this);
    followCameraComponent = new FollowCameraComponent(this);
    followCameraComponent->snapToIdeal();
}

void RacingCarActor::actorInput(const InputState &inputState) {
    float forwardSpeed = 0.0f;
    float angularSpeed = 0.0f;
    // wasd movement
    if (inputState.keyboard.getKeyValue(SDL_SCANCODE_W)) {
        forwardSpeed += 400.0f;
    }
    if (inputState.keyboard.getKeyValue(SDL_SCANCODE_S)) {
        forwardSpeed -= 400.0f;
    }
    if (inputState.keyboard.getKeyValue(SDL_SCANCODE_A)) {
        angularSpeed -= Maths::pi;
    }
    if (inputState.keyboard.getKeyValue(SDL_SCANCODE_D)) {
        angularSpeed += Maths::pi;
    }

    moveComponent->setForwardSpeed(forwardSpeed);
    moveComponent->setAngularSpeed(angularSpeed);

    // Adjust horizontal distance of camera based on speed
    if (!Maths::nearZero(forwardSpeed)) {
        followCameraComponent->setHorizontalDistance(500.0f);
    } else {
        followCameraComponent->setHorizontalDistance(350.0f);
    }
}

void RacingCarActor::setVisible(bool isVisibleP) {
    meshComponent->setVisible(isVisibleP);
}
