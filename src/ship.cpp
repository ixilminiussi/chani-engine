#include "ship.h"

#include "spriteComponent.h"
#include "assets.h"
#include "inputComponent.h"
#include "maths.h"

Ship::Ship() : Actor() {
    SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Ship"));
    InputComponent* ic = new InputComponent(this);
    ic -> setMaxForwardSpeed(300.0f);
    ic -> setMaxAngularSpeed(Maths::pi * 2);
}
