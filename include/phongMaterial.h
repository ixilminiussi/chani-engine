#if !defined(PHONG_MATERIAL_H)
#define PHONG_MATERIAL_H

#include "material.h"

class PhongMaterial : public Material {
  public:
    PhongMaterial();
    ~PhongMaterial() = default;

    void use() override;

    void setSpecular(const float &specularP) { specular = specularP; }

  protected:
    float specular;
};

#endif
