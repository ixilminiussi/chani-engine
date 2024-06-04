#include "ship.h"

#include "spriteComponent.h"
#include "assets.h"
#include "inputComponent.h"
#include "maths.h"
#include "laser.h"

Ship::Ship() : 
    Actor(),
    laserCooldown(0.f)
{
    SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Ship"));
    InputComponent* ic = new InputComponent(this);
    ic -> setMaxForwardSpeed(300.0f);
    ic -> setMaxAngularSpeed(Maths::pi * 2);
}

void Ship::actorInput(Uint8 const* keyState) {
    if (keyState[SDL_SCANCODE_SPACE] && laserCooldown <= 0.f) {
        Laser*laser = new Laser();
        laser -> setPosition(getPosition());
        laser -> setRotation(getRotation());
        laserCooldown = 0.2f;
    }
}

void Ship::updateActor(float dt) {
    laserCooldown -= dt;
}
