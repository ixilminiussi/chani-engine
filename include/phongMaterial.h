#if !defined(PHONG_MATERIAL_H)
#define PHONG_MATERIAL_H

#include "material.h"

class PhongMaterial : public Material
{
  public:
    PhongMaterial();
    ~PhongMaterial() = default;

    void use() override;

    Material *makeUnique() override;

    void setSpecular(const float &specularP);

  protected:
    float specular;
};

#endif
