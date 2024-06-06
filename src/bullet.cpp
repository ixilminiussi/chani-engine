#include "bullet.h"

#include "spriteComponent.h"
#include "moveComponent.h"
#include "circleCollisionComponent.h"
#include "game.h"
#include "enemy.h"
#include "assets.h"

Bullet::Bullet() {
    SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Projectile"));
    MoveComponent* mc = new MoveComponent(this);
    mc -> setForwardSpeed(400.f);
    circle = new CircleCollisionComponent(this);
    circle -> setRadius(5.f);
    lifetime = 1.f;
}

void Bullet::updateActor(float dt) {
    Actor::updateActor(dt);

    for (Enemy* e : getGame().getEnemies()) {
        if (Intersect(*circle, e -> getCircle())) {
            e -> setState(ActorState::Dead);
            setState(ActorState::Dead);
            break;
        }
    }

    lifetime -= dt;
    if (lifetime <= 0.f) {
        setState(ActorState::Dead);
    }
}
