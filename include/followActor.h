#if !defined(FOLLOW_ACTOR_H)
#define FOLLOW_ACTOR_H

#include "actor.h"

class FollowActor : public Actor {
  public:
    FollowActor();

    void actorInput(const InputState &inputState) override;
    void setVisible(bool isVisibleP);

  private:
    class MoveComponent *moveComponent;
    class FollowCameraComponent *cameraComponent;
    class MeshComponent *meshComponent;
};

#endif
