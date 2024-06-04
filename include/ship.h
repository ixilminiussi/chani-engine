#if !defined SHIP_H
#define SHIP_H

#include <SDL2/SDL_stdinc.h>
#include "actor.h"

class Ship : public Actor {
public:
    Ship();

    void actorInput(Uint8 const* keyState) override;
    void updateActor(float dt) override;

private:
    float laserCooldown;
};

#endif
