#if !defined(RACING_CAR_ACTOR_H)
#define RACING_CAR_ACTOR_H

#include <actor.h>
#include <moveComponent.h>
#include <followCameraComponent.h>
#include <meshComponent.h>

class RacingCarActor : public Actor {
  public:
    RacingCarActor();

    void actorInput(const InputState &inputState) override;
    void setVisible(bool isVisibleP);

  private:
    MoveComponent *moveComponent;
    FollowCameraComponent *followCameraComponent;
    MeshComponent *meshComponent;
};

#endif
