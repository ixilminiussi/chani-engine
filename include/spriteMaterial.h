#if !defined(SPRITE_MATERIAL_H)
#define SPRITE_MATERIAL_H

#include "material.h"

class SpriteMaterial : public Material
{
  public:
    SpriteMaterial();
    ~SpriteMaterial() = default;

    void use() override;

    Material *makeUnique() override;
};

#endif
