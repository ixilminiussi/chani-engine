#if !defined ACTOR_H
#define ACTOR_H

#include <vector>
#include <SDL2/SDL_stdinc.h>
#include "vector2.h"

class Game;
class Component;

class Actor {
public:
    enum class ActorState {
        Active, Paused, Dead
    };

    Actor();
    virtual ~Actor();
    Actor(Actor const&) = delete;
    Actor& operator=(Actor const&) = delete;

    Game& getGame() const { return game; }
    const ActorState getState() const { return state; }
    const Vector2 getPosition() const { return position; }
    const float getScale() const { return scale; }
    const float getRotation() const { return rotation; }
    Vector2 getForward() const;

    void setPosition(Vector2 positionP);
    void setScale(float scaleP);
    void setRotation(float rotationP);
    void setState(ActorState stateP);

    void update(float dt);
    void updateComponents(float dt);
    virtual void updateActor(float dt);

    void addComponent(Component* component);
    void removeComponent(Component* component);

    void processInput(Uint8 const* keyState);
    virtual void actorInput(Uint8 const* keyState);

private:
    Game& game;
    ActorState state;
    Vector2 position;
    float scale;
    float rotation;

    std::vector<Component*> components;
};

#endif
