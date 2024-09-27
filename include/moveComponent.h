#if !defined(MOVE_COMPONENT_H)
#define MOVE_COMPONENT_H

#include "component.h"

class MoveComponent : public Component
{
  public:
    MoveComponent(Actor *ownerP,
                  int updateOrder = 10); // By default, update before other components
    MoveComponent() = delete;
    MoveComponent(const MoveComponent &) = delete;
    MoveComponent &operator=(const MoveComponent &) = delete;

    float getForwardSpeed() const;
    float getAngularSpeed() const;
    float getStrafeSpeed() const;

    void setForwardSpeed(float forwardSpeedP);
    void setAngularSpeed(float angularSpeedP);
    void setStrafeSpeed(float strafeSpeedP);

    void update(float dt) override;

  private:
    float forwardSpeed;
    float angularSpeed;
    float strafeSpeed;
};

#endif
