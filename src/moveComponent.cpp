#include "moveComponent.h"

#include "actor.h"
#include "maths.h"

MoveComponent::MoveComponent(Actor *ownerP, int updateOrderP)
    : Component(ownerP, updateOrderP), forwardSpeed(0.0f), angularSpeed(0.0f), strafeSpeed(0.0f)
{
}

float MoveComponent::getForwardSpeed() const
{
    return forwardSpeed;
}

void MoveComponent::setForwardSpeed(float forwardSpeedP)
{
    forwardSpeed = forwardSpeedP;
}

float MoveComponent::getAngularSpeed() const
{
    return angularSpeed;
}

void MoveComponent::setAngularSpeed(float angularSpeedP)
{
    angularSpeed = angularSpeedP;
}

float MoveComponent::getStrafeSpeed() const
{
    return strafeSpeed;
}

void MoveComponent::setStrafeSpeed(float strafeSpeedP)
{
    strafeSpeed = strafeSpeedP;
}

void MoveComponent::update(float dt)
{
    if (!Maths::nearZero(angularSpeed))
    {
        Quaternion newRotation = owner.getRotation();
        float angle = angularSpeed * dt;
        Quaternion increment(Vector3::unitZ, angle);
        newRotation = Quaternion::concatenate(newRotation, increment);
        owner.setRotation(newRotation);
    }
    if (!Maths::nearZero(forwardSpeed) || !Maths::nearZero(strafeSpeed))
    {
        Vector3 newPosition = owner.getPosition();
        newPosition += owner.getForward() * forwardSpeed * dt;
        newPosition += owner.getRight() * strafeSpeed * dt;
        owner.setPosition(newPosition);
    }
}
