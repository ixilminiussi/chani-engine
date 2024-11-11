#include "cameraComponent.h"

#include "chani.h"

CameraComponent::CameraComponent(Actor *owner, int updateOrder) : Component(owner, updateOrder)
{
}

void CameraComponent::setViewMatrix(const Matrix4<float> &view)
{
    Game &game = owner.getGame();
    game.getRenderer().setViewMatrix(view);
    game.getAudioSystem().setListener(view);
}
