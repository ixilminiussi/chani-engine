#include "orbitCameraComponent.h"

#include "actor.h"

OrbitCameraComponent::OrbitCameraComponent(Actor *ownerP)
    : CameraComponent(ownerP), offset(-400.0f, 0.0f, 0.0f), up(Vector3::unitZ), pitchSpeed(0.0f), yawSpeed(0.0f)
{
}

void OrbitCameraComponent::update(float dt)
{
    CameraComponent::update(dt);

    Quaternion yaw{Vector3::unitZ, yawSpeed * dt};
    offset = Vector3::transform(offset, yaw);
    up = Vector3::transform(up, yaw);

    // Compute camera forward/right from these vectors
    // Forward owner.position - (owner.position + offset) = -offset
    Vector3 forward = -1.0f * offset;
    forward.normalize();
    Vector3 right = Vector3::cross(up, forward);
    right.normalize();

    Quaternion pitch{right, pitchSpeed * dt};
    offset = Vector3::transform(offset, pitch);
    up = Vector3::transform(up, pitch);

    Vector3 target = owner.getPosition();
    Vector3 cameraPosition = target + offset;
    Matrix4 view = Matrix4::createLookAt(cameraPosition, target, up);
    setViewMatrix(view);
}

float OrbitCameraComponent::getDistance()
{
    return (offset - owner.getPosition()).length();
}

void OrbitCameraComponent::setDistance(float newDistance)
{
    float currentDistance = getDistance();
    unzoom(newDistance - getDistance());
}

void OrbitCameraComponent::zoom(float factor)
{
    if (factor > getDistance())
    {
        setDistance(0.0f);
        return;
    }
    Vector3 forward = -1.0f * offset;
    forward.normalize();
    offset += forward * factor;
}

void OrbitCameraComponent::unzoom(float factor)
{
    zoom(-factor);
}

float OrbitCameraComponent::getPitchSpeed() const
{
    return pitchSpeed;
}

void OrbitCameraComponent::setPitchSpeed(float pitchSpeedP)
{
    pitchSpeed = pitchSpeedP;
}

float OrbitCameraComponent::getYawSpeed() const
{
    return yawSpeed;
}

void OrbitCameraComponent::setYawSpeed(float yawSpeedP)
{
    yawSpeed = yawSpeedP;
}
