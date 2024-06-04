#if !defined(LASER_H)
#define LASER_H

#include "actor.h"
#include "circleCollisionComponent.h"

class Laser : public Actor {
public: 
    Laser();

    void updateActor(float dt) override;
private:
    CircleCollisionComponent* collision;
    float deathTimer;
};

#endif
