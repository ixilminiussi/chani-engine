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
    void reload();
    void setScale(float *scale);
    void setStrength(float *strength);
    void setPersistence(float *persistence);

  protected:
    Cuboid *area;
    Actor *camera;
    float *persistence, *scale, *strength;
    PerlinNoise noise1;
    PerlinNoise noise2;
    PerlinNoise noise3;
};

#endif
