#if !defined(PBR_MATERIAL_H)
#define PBR_MATERIAL_H

#include "material.h"

class PBRMaterial : public Material
{
  public:
    PBRMaterial();
    ~PBRMaterial() = default;

    void use() override;

    Material *makeUnique() override;

    void setRoughness(const float &roughnessP);

    static Material *loadFromFile(const std::string &filename);

  protected:
    float roughness;

    // TODO: let users decide between a value and a texture. In the case of a
    // texture, roughness/albedo etc will be determined according to that
    // texture, otherwise it will be the value.
};

#endif
