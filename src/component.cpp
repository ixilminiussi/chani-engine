#include "component.h"

#include "actor.h"
#include "inputSystem.h"

Component::Component(Actor *ownerP, int updateOrderP) : owner(*ownerP), updateOrder(updateOrderP)
{
    owner.addComponent(this);
}

Component::~Component()
{
    owner.removeComponent(this);
}

int Component::getUpdateOrder() const
{
    return updateOrder;
}

void Component::processInput(const InputState &inputState)
{
}

void Component::update(float dt)
{
}
