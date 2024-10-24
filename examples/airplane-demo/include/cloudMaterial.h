#if !defined(CLOUD_MATERIAL_H)
#define CLOUD_MATERIAL_H

#include "material.h"
#include "shapes.h"
#include <actor.h>

class CloudMaterial : public Material {
  public:
    CloudMaterial();
    ~CloudMaterial() = default;

    void use() override;

    Material *makeUnique() override;

    static Material *loadFromFile(const std::string &filename);
    void setArea(Cuboid *cuboid);

  protected:
    Cuboid *area;
    Actor *camera;
};

#endif
