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

    float cloudTransmittanceScale = 1.3f;
    float cloudFloor = 0.3f;
    float cloudScale = 1.2f;
    float cloudStrength = 0.78f;
    float cloudLightAbsorption = 1.0f;
    float cloudDarknessThreshold = 0.2f;
    Vector3<float> cloudSquish = Vector3(1.0f, 1.0f, 0.7f);
    float cloudColor[3] = {0.9f, 0.95f, 1.0f};
    int timeScale = 25;
    class Cuboid *area;
};

#endif
