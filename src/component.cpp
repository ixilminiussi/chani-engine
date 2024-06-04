#include "component.h"

#include "log.h"
#include "actor.h"

Component::Component(Actor* ownerP, int updateOrderP) : 
    owner(*ownerP), 
    updateOrder(updateOrderP) {
    owner.addComponent(this);
}

Component::~Component() {
    owner.removeComponent(this);
}

void Component::update(float dt) {
}

void Component::processInput(Uint8 const* keyState) {}
