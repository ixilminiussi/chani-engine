#include "enemy.h"

#include "game.h"
#include "assets.h"
#include "navComponent.h"
#include "maths.h" 
#include "tile.h"
#include <algorithm>

Enemy::Enemy() :
    Actor(),
    circle(nullptr)
{
    getGame().getEnemies().emplace_back(this);

    SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Airplane"));
    setPosition(getGame().getGrid().getStartTile().getPosition());
    NavComponent* nc = new NavComponent(this);
    nc -> setForwardSpeed(150.f);
    nc -> startPath(getGame().getGrid().getStartTile());
    circle = new CircleCollisionComponent(this);
    circle -> setRadius(25.f);
}

Enemy::~Enemy() {
    std::vector<Enemy*>& enemies = getGame().getEnemies();
    auto iter = std::find(begin(enemies), end(enemies), this);
    enemies.erase(iter);
}

void Enemy::updateActor(float dt) {
    Actor::updateActor(dt);

    Vector2 dist = getPosition() - getGame().getGrid().getEndTile().getPosition();
    if (Maths::nearZero(dist.length(), 10.f)) {
        setState(ActorState::Dead);
    }
}
