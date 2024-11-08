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
    CloudMaterial() = delete;
    CloudMaterial(PerlinSettings perlinSettings);
    ~CloudMaterial() = default;

    void use() override;

    Material *makeUnique() override;

    static Material *loadFromFile(const std::string &filename, const PerlinSettings &perlinSettings);
    void setArea(Cuboid *cuboid);
    void reload();

  protected:
    Cuboid *area;
    Actor *camera;
    PerlinNoise noise;
};

#endif
