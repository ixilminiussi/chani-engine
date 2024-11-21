#if !defined(CLOUD_MATERIAL_H)
#define CLOUD_MATERIAL_H

#include "material.h"
#include "perlinNoise.h"
#include "shapes.h"
#include <actor.h>
#include <computeShader.h>

class CloudMaterial : public Material
{
  public:
    CloudMaterial();
    ~CloudMaterial() = default;

    void use() override;

    Material *makeUnique() override;

    static Material *loadFromFile(const std::string &filename);
    void setArea(Cuboid *cuboid);
    void setScale(float *scale);
    void setSquish(Vector3<float> *squash);
    void setFloor(float *floor);
    void setStrength(float *strength);
    void setTransmittance(float *transmittance);
    void setLightAbsorption(float *lightAbsorption);
    void setDarknessThreshold(float *darknessThreshold);
    void setTimeScale(int *timeScale);
    void setColor(float *cloudColor);
    void addNoise(const PerlinSettings &perlinSettings);
    void makeUI();

  protected:
    Cuboid *area;
    Actor *camera;
    float *scale, *strength, *floor, *transmittance, *lightAbsorption, *darknessThreshold;
    float *cloudColor;
    Vector3<float> *squish;
    int *timeScale;
    PerlinNoise noise[10];
    uint noiseCount = 0u;
};

#endif
