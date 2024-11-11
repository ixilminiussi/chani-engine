#include "actor.h"

#include "chani.h"
#include "component.h"

#include <algorithm>

Actor::Actor()
    : state(Actor::ActorState::Active), position(Vector3<float>::zero()), scale(1.0f), rotation(Quaternion::identity),
      mustRecomputeWorldTransform(true), game(Game::instance())
{
    game.addActor(this);
}

Actor::~Actor()
{
    game.removeActor(this);
    // Need to delete components
    // Because ~Component calls RemoveComponent, need a different style loop
    while (!components.empty())
    {
        delete components.back();
    }
}

Game &Actor::getGame() const
{
    return game;
}

const Actor::ActorState Actor::getState() const
{
    return state;
}

const Vector3<float> Actor::getPosition() const
{
    return position;
}

void Actor::setPosition(Vector3<float> positionP)
{
    position = positionP;
    mustRecomputeWorldTransform = true;
}

const float Actor::getScale() const
{
    return scale;
}

void Actor::setScale(float scaleP)
{
    scale = scaleP;
    mustRecomputeWorldTransform = true;
}

const Quaternion Actor::getRotation() const
{
    return rotation;
}

void Actor::setRotation(Quaternion rotationP)
{
    rotation = rotationP;
    mustRecomputeWorldTransform = true;
}

void Actor::rotate(const Vector3<float> &axis, float angle)
{
    Quaternion newRotation = rotation;
    Quaternion increment(axis, angle);
    newRotation = Quaternion::concatenate(newRotation, increment);
    setRotation(newRotation);
}

void Actor::setAngle(const Vector3<float> &axis, float angle)
{
    Quaternion newRotation(axis, angle);
    setRotation(newRotation);
}

void Actor::setState(ActorState stateP)
{
    state = stateP;
}

Vector3<float> Actor::getForward() const
{
    return Vector3<float>::transform(Vector3<float>::unitX(), rotation);
}

Vector3<float> Actor::getRight() const
{
    return Vector3<float>::transform(Vector3<float>::unitY(), rotation);
}

const Matrix4<float> &Actor::getWorldTransform() const
{
    return worldTransform;
}

void Actor::computeWorldTransform()
{
    if (mustRecomputeWorldTransform)
    {
        mustRecomputeWorldTransform = false;
        worldTransform = Matrix4<float>::createScale(scale);
        worldTransform *= Matrix4<float>::createFromQuaternion(rotation);
        worldTransform *= Matrix4<float>::createTranslation(position);

        for (auto component : components)
        {
            component->onUpdateWorldTransform();
        }
    }
}

void Actor::processInput(const InputState &inputState)
{
    if (state == Actor::ActorState::Active)
    {
        for (auto component : components)
        {
            component->processInput(inputState);
        }
        actorInput(inputState);
    }
}

void Actor::actorInput(const InputState &inputState)
{
}

void Actor::update(float dt)
{
    if (state == Actor::ActorState::Active)
    {
        computeWorldTransform();
        updateComponents(dt);
        updateActor(dt);
        computeWorldTransform();
    }
}

void Actor::updateComponents(float dt)
{
    for (auto component : components)
    {
        component->update(dt);
    }
}

void Actor::updateActor(float dt)
{
}

void Actor::addComponent(Component *component)
{
    // Find the insertion point in the sorted vector
    // (The first element with a order higher than me)
    int myOrder = component->getUpdateOrder();
    auto iter = begin(components);
    for (; iter != end(components); ++iter)
    {
        if (myOrder < (*iter)->getUpdateOrder())
        {
            break;
        }
    }

    // Inserts element before position of iterator
    components.insert(iter, component);
}

void Actor::removeComponent(Component *component)
{
    auto iter = std::find(begin(components), end(components), component);
    if (iter != end(components))
    {
        components.erase(iter);
    }
}
