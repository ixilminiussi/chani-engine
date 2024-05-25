#include "../include/asteroid.h"
#include "../include/random.h"
#include "../include/window.h"
#include "../include/maths.h"
#include "../include/spriteComponent.h"
#include "../include/moveComponent.h"
#include "../include/assets.h"

Asteroid::Asteroid() : Actor() {
    Vector2 randPos = Random::getVector(Vector2::zero, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT));
    setPosition(randPos);
    setRotation(Random::getFloatRange(0.f, Maths::twoPi));

    SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Asteroid"));
    MoveComponent* mc = new MoveComponent(this);
    mc -> setForwardSpeed(150.0f);
}
