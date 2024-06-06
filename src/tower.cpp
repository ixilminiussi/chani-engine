#include "tower.h"

#include "spriteComponent.h"
#include "moveComponent.h"
#include "game.h"
#include "enemy.h"
#include "bullet.h"
#include "assets.h"
#include "maths.h"

Tower::Tower() : Actor() {
    SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Tower"), 200);
    move = new MoveComponent(this);
    nextAttackTimer = ATTACK_TIME;
}

void Tower::updateActor(float dt) {
    Actor::updateActor(dt);

    nextAttackTimer -= dt;
    if (nextAttackTimer <= 0.f) {
        Enemy* e = getGame().getNearestEnemy(getPosition());
        if (e != nullptr) {
            Vector2 dir = e -> getPosition() - getPosition();
            float dist = dir.length();
            if (dist < ATTACK_RANGE) {
                setRotation(Maths::atan2(-dir.y, dir.x));
                Bullet* b = new Bullet();
                b -> setPosition(getPosition());
                b -> setRotation(getRotation());
            }
        }
        nextAttackTimer += ATTACK_TIME;
    }
}
