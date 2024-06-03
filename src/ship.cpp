#include "../include/ship.h"
#include "../include/spriteComponent.h"
#include "../include/assets.h"
#include "../include/inputComponent.h"
#include "../include/maths.h"

Ship::Ship() : Actor() {
    SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Ship"));
    InputComponent* ic = new InputComponent(this);
    ic -> setMaxForwardSpeed(300.0f);
    ic -> setMaxAngularSpeed(Maths::pi * 2);
}
