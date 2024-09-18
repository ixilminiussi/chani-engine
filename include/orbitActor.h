#if !defined(ORBIT_ACTOR_H)
#define ORBIT_ACTOR_H

#include "actor.h"

class OrbitActor : public Actor {
  public:
    OrbitActor();
    void actorInput(const InputState &inputState) override;
    void setVisible(bool visible);

  private:
    class OrbitCameraComponent *cameraComponent;
    class MeshComponent *meshComponent;
};

#endif
