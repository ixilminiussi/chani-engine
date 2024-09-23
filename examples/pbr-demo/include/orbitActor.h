#if !defined(ORBIT_ACTOR_H)
#define ORBIT_ACTOR_H

#include <actor.h>
#include <inputSystem.h>
#include <orbitCameraComponent.h>

class OrbitActor : public Actor {
  public:
    OrbitActor();
    void actorInput(const InputState &inputState) override;
    void snapToActor(Actor *actor);
    void updateActor(float dt) override;

  private:
    Actor *targetActor;
    OrbitCameraComponent *orbitCameraComponent;
    Vector2 prevMousePosition;
};

#endif
