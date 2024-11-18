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
    void setFloor(float *floor);
    void setStrength(float *strength);
    void setPersistence(float *persistence);
    void setSize(float **size);

  protected:
    Cuboid *area;
    Actor *camera;
    float *persistence, *scale, *strength, *floor;
    float **size;
    PerlinNoise noise1;
    PerlinNoise noise2;
    PerlinNoise noise3;
    PerlinNoise noise4;
};

#endif
