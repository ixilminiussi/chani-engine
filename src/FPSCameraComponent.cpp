#include "FPSCameraComponent.h"

FPSCameraComponent::FPSCameraComponent(Actor *ownerP)
    : CameraComponent(ownerP), pitchSpeed(0.0f), maxPitch(Maths::pi / 3.0f), pitch(0.0f)
{
}

void FPSCameraComponent::update(float dt)
{
    CameraComponent::update(dt);

    Vector3<float> cameraPosition = owner.getPosition();
    pitch += pitchSpeed * dt;
    pitch = Maths::clamp(pitch, -maxPitch, maxPitch);
    Quaternion q{owner.getRight(), pitch};
    Vector3<float> viewForward = Vector3<float>::transform(owner.getForward(), q);

    Vector3<float> target = cameraPosition + viewForward * 100.0f;
    Vector3<float> up = Vector3<float>::transform(Vector3<float>::unitZ(), q);
    Matrix4<float> view = Matrix4<float>::createLookAt(cameraPosition, target, up);
    setViewMatrix(view);
}

float FPSCameraComponent::getPitch() const
{
    return pitch;
}

float FPSCameraComponent::getPitchSpeed() const
{
    return pitchSpeed;
}

void FPSCameraComponent::setPitchSpeed(float speed)
{
    pitchSpeed = speed;
}

float FPSCameraComponent::getMaxPitch() const
{
    return maxPitch;
}

void FPSCameraComponent::setMaxPitch(float pitch)
{
    maxPitch = pitch;
}
