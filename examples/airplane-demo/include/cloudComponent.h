#include "cloudMaterial.h"
#if !defined(CLOUD_H)
#define CLOUD_H

#include <actor.h>
#include <computeShader.h>
#include <postProcessComponent.h>
#include <shader.h>
#include <shapes.h>

class CloudComponent : public PostProcessComponent
{
  public:
    CloudComponent(Actor *owner, Cuboid *cuboid);

    void update(float dt) override;
    void makeUI();

  private:
    ComputeShader perlinNoiseCS;
    CloudMaterial *cloudMaterial;

    float cloudFloor = 0.2f;
    float cloudScale = 1.2f;
    float persistence = 0.5f;
    float cloudStrength = 0.6f;
    int timeScale = 0;
    class Cuboid *area;
};

#endif
