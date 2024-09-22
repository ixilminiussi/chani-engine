#if !defined(MESH_COMPONENT_H)
#define MESH_COMPONENT_H

#include "component.h"
#include "material.h"

class MeshComponent : public Component {
  public:
    MeshComponent(Actor *owner);
    virtual ~MeshComponent();

    bool getVisible() const { return isVisible; }
    void setVisible(bool isVisibleP) { isVisible = isVisibleP; }

    virtual void draw();
    virtual void setMesh(class Mesh &meshP);
    void setTextureIndex(size_t textureIndexP);

    void setMaterial(Material &materialP) { material = &materialP; }

  protected:
    Material *material;
    Mesh *mesh;
    size_t textureIndex;
    bool isVisible;
};

#endif
