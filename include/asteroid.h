#if !defined(ASTEROID_H)
#define ASTEROID_H

#include "actor.h"
#include "circleCollisionComponent.h"

class Asteroid : public Actor {
public:
    Asteroid();
    ~Asteroid();

    CircleCollisionComponent& getCollision() { return *collision; }

private:
    CircleCollisionComponent* collision;
};

#endif
