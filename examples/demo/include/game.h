#if !defined(GAME_H)
#define GAME_H

#include "FPSActor.h"
#include "racingCarActor.h"

#include <orbitActor.h>
#include <soundEvent.h>
#include <splineActor.h>
#include <spriteComponent.h>

void changeCamera(int mode);

FPSActor *fps;
RacingCarActor *racingCar;
OrbitActor *orbit;
SplineActor *path;
SpriteComponent *crosshair;
SoundEvent musicEvent;

#endif
