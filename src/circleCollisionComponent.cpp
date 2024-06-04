#include "circleCollisionComponent.h"

#include "actor.h"

CircleCollisionComponent::CircleCollisionComponent(Actor* owner) :
    Component(owner),
    radius(1.f)
{}

float CircleCollisionComponent::getRadius() const {
    return owner.getScale() * radius;
}

void CircleCollisionComponent::setRadius(float radiusP) {
    radius = radiusP;
}

const Vector2 CircleCollisionComponent::getCenter() const {
    return owner.getPosition();
}

bool Intersect(CircleCollisionComponent const& a, CircleCollisionComponent const& b) {
    Vector2 ab = b.getCenter() - a.getCenter();
    float distSq = ab.lengthSq();
    float sumOfRadius = a.getRadius() + b.getRadius();
    return distSq <= sumOfRadius * sumOfRadius;
}
