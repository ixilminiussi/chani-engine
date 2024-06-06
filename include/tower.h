#if !defined(TOWER_H)
#define TOWER_H

#include "actor.h"
#include "moveComponent.h"

class Tower : public Actor {
public:
    Tower();
    void updateActor(float dt) override;

private:
    MoveComponent* move;
    float nextAttackTimer;
    const float ATTACK_TIME = 2.5f;
    const float ATTACK_RANGE = 100.f;
};

#endif
