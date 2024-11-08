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

    void reloadNoiseShader();

  private:
    ComputeShader perlinNoiseCS;
    CloudMaterial *cloudMaterial;
};

#endif
