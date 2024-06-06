#include "navComponent.h"
#include "actor.h"
#include "tile.h"
#include "maths.h"

NavComponent::NavComponent(Actor* owner, int updateOrder) :
    MoveComponent(owner, updateOrder),
    nextNode(nullptr)
{}

void NavComponent::update(float dt) {
    if (nextNode) {
        Vector2 dist = owner.getPosition() - nextNode -> getPosition();
        if (Maths::nearZero(dist.length(), 2.0f)) {
            nextNode = nextNode -> getParent();
            turnTo(nextNode -> getPosition());
        }
    }
    MoveComponent::update(dt);
}

void NavComponent::startPath(Tile const& start) {
    nextNode = start.getParent();
    turnTo(nextNode -> getPosition());
}

void NavComponent::turnTo(Vector2 const& targetPosition) {
    Vector2 dir = targetPosition - owner.getPosition();
    float angle = Maths::atan2(-dir.y, dir.x);
    owner.setRotation(angle);
}
