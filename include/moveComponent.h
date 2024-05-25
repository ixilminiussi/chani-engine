#if !defined(MOVE_COMPONENT_H)
#define MOVE_COMPONENT_H

#include "component.h"

class MoveComponent : public Component {
public:
    MoveComponent(Actor* ownerP, int updateOrder = 10);
    MoveComponent() = delete;
    MoveComponent& operator=(const MoveComponent&) = delete;

    float getForwardSpeed() const { return forwardSpeed; }
    float getAngularSpeed() const { return angularSpeed; }

    void setForwardSpeed(float forwardSpeedP);
    void setAngularSpeed(float angularSpeedP);

    void update(float dt) override;

private:
    float forwardSpeed;
    float angularSpeed;
};

#endif
