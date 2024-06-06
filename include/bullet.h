#if !defined(BULLET_H)
#define BULLET_H

#include "actor.h"
#include "circleCollisionComponent.h"

class Bullet : public Actor {
public:
    Bullet();
    void updateActor(float dt) override;

private: 
    CircleCollisionComponent* circle;
    float lifetime;
};

#endif
