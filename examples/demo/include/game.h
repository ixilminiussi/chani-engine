#if !defined(GAME_H)
#define GAME_H

#include "racingCarActor.h"
#include "FPSActor.h"

#include <spriteComponent.h>
#include <orbitActor.h>
#include <splineActor.h>
#include <spriteComponent.h>
#include <soundEvent.h>

void changeCamera(int mode);

FPSActor *fps;
RacingCarActor *racingCar;
OrbitActor *orbit;
SplineActor *path;
SpriteComponent *crosshair;
SoundEvent musicEvent;

#endif
