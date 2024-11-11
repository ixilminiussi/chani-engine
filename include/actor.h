#if !defined(ACTOR_H)
#define ACTOR_H

#include "matrix4.h"

#include <SDL_stdinc.h>
#include <vector>

class Game;
class Component;

class Actor
{
  public:
    enum class ActorState
    {
        Active,
        Paused,
        Dead
    };

    Actor();
    virtual ~Actor();
    Actor(const Actor &) = delete;
    Actor &operator=(const Actor &) = delete;

    Game &getGame() const;
    const ActorState getState() const;
    const Vector3<float> getPosition() const;
    const float getScale() const;
    const Quaternion getRotation() const;
    const Matrix4<float> &getWorldTransform() const;

    void setPosition(Vector3<float> positionP);
    void setScale(float scaleP);
    void setRotation(Quaternion rotationP);
    void setState(ActorState stateP);

    void setAngle(const Vector3<float> &axis, float angle);
    void rotate(const Vector3<float> &axis, float angle);
    Vector3<float> getForward() const;
    Vector3<float> getRight() const;
    void computeWorldTransform();

    void processInput(const struct InputState &inputState);
    virtual void actorInput(const struct InputState &inputState);
    void update(float dt);
    void updateComponents(float dt);
    virtual void updateActor(float dt);
    void addComponent(Component *component);
    void removeComponent(Component *component);

  private:
    Game &game;
    ActorState state;
    Vector3<float> position;
    float scale;
    Quaternion rotation;
    Matrix4<float> worldTransform;
    bool mustRecomputeWorldTransform;

    std::vector<Component *> components;
};

#endif
