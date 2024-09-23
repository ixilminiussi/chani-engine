#if !defined(FPS_ACTOR_H)
#define FPS_ACTOR_H

#include "actor.h"
#include "soundEvent.h"
#include "vector3.h"

class FPSActor : public Actor {
  public:
    FPSActor();

    void updateActor(float dt) override;
    void actorInput(const struct InputState &inputState) override;

    void setFootstepSurface(float value);
    void setVisible(bool isVisible);

  private:
    class MoveComponent *moveComponent;
    class AudioComponent *audioComponent;
    class MeshComponent *meshComponent;
    class FPSCameraComponent *cameraComponent;
    class Actor *FPSModel;
    SoundEvent footstep;
    float lastFootstep;
};

const Vector3 MODEL_OFFSET = Vector3(10.0f, 10.0f, -10.0f);

#endif
