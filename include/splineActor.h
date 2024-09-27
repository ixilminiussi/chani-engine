#if !defined(SPLINE_ACTOR_H)
#define SPLINE_ACTOR_H

#include "actor.h"

class SplineActor : public Actor
{
  public:
    SplineActor();

    void actorInput(const InputState &inputState) override;
    void restartSpline();

  private:
    class SplineCameraComponent *cameraComponent;
};

#endif
