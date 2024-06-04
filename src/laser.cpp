#include "laser.h"

#include <vector>
#include "spriteComponent.h"
#include "assets.h"
#include "moveComponent.h"
#include "game.h"
#include "asteroid.h"

Laser::Laser() :
    Actor(),
    deathTimer(1.f),
    collision(nullptr) 
{
    new SpriteComponent(this, Assets::getTexture("Laser"));
    MoveComponent* mc = new MoveComponent(this);
    mc -> setForwardSpeed(800.f);
    collision = new CircleCollisionComponent(this);
    collision -> setRadius(11.f);
}

void Laser::updateActor(float dt) {
    deathTimer -= dt;
    if (deathTimer <= 0.f) {
        setState(ActorState::Dead);
    } else {
        std::vector<Asteroid*> asteroids = getGame().getAsteroids();

        for (Asteroid* asteroid : asteroids) {
            if (Intersect(*collision, asteroid -> getCollision())) {
                setState(ActorState::Dead);
                asteroid -> setState(ActorState::Dead);
                break;
            }
        }
    }
}
