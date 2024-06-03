#include "../include/component.h"
#include "../include/log.h"
#include "../include/actor.h"

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
