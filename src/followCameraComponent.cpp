#include "followCameraComponent.h"

#include "actor.h"

FollowCameraComponent::FollowCameraComponent(Actor *ownerP)
    : CameraComponent(ownerP), horizontalDistance(FOLLOW_HORIZONTAL_DISTANCE),
      verticalDistance(FOLLOW_VERTICAL_DISTANCE), targetDistance(FOLLOW_TARGET_DISTANCE),
      springConstant(FOLLOW_SPRING_CONSTANT)
{
}

void FollowCameraComponent::update(float dt)
{
    CameraComponent::update(dt);

    float dampening = 2.0f * Maths::sqrt(springConstant);
    Vector3<float> idealPosition = computeCameraPosition();
    Vector3<float> diff = actualPosition - idealPosition;
    Vector3<float> accel = -springConstant * diff - dampening * velocity;
    velocity += accel * dt;
    actualPosition += velocity * dt;

    Vector3<float> target = owner.getPosition() + owner.getForward() * targetDistance;
    Matrix4<float> view = Matrix4<float>::createLookAt(actualPosition, target, Vector3<float>::unitZ());
    setViewMatrix(view);
}

void FollowCameraComponent::snapToIdeal()
{
    actualPosition = computeCameraPosition();
    velocity = Vector3<float>::zero();
    Vector3<float> target = owner.getPosition() + owner.getForward() * targetDistance;
    Matrix4<float> view = Matrix4<float>::createLookAt(actualPosition, target, Vector3<float>::unitZ());
    setViewMatrix(view);
}

void FollowCameraComponent::setHorizontalDistance(float distance)
{
    horizontalDistance = distance;
}

void FollowCameraComponent::setVerticalDistance(float distance)
{
    verticalDistance = distance;
}

void FollowCameraComponent::setTargetDistance(float distance)
{
    targetDistance = distance;
}

void FollowCameraComponent::setSpringConstant(float springConstantP)
{
    springConstant = springConstantP;
}

Vector3<float> FollowCameraComponent::computeCameraPosition() const
{
    Vector3<float> cameraPosition = owner.getPosition();
    cameraPosition -= owner.getForward() * horizontalDistance;
    cameraPosition += Vector3<float>::unitZ() * verticalDistance;
    return cameraPosition;
}
