#if !defined(ENEMY_H)
#define ENEMY_H

#include "actor.h"
#include "circleCollisionComponent.h"

class Enemy : public Actor
{
public:
    Enemy();
    virtual ~Enemy();
    void updateActor(float dt) override;

    CircleCollisionComponent& getCircle() { return *circle; }

private:
    CircleCollisionComponent* circle;
};

#endif
