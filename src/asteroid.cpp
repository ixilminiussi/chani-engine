#include "asteroid.h"

#include "random.h"
#include "window.h"
#include "maths.h"
#include "spriteComponent.h"
#include "moveComponent.h"
#include "assets.h"
#include "game.h"

Asteroid::Asteroid() : Actor() {
    Vector2 randPos = Random::getVector(Vector2::zero, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT));
    setPosition(randPos);
    setRotation(Random::getFloatRange(0.f, Maths::twoPi));

    SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Asteroid"));
    MoveComponent* mc = new MoveComponent(this);
    mc -> setForwardSpeed(150.0f);

    collision = new CircleCollisionComponent(this);
    collision->setRadius(40.f);

    getGame().addAsteroid(this);
}

Asteroid::~Asteroid() {
    getGame().removeAsteroid(this);
}
