#if !defined(MESH_COMPONENT_H)
#define MESH_COMPONENT_H

#include "component.h"
#include "material.h"
#include "mesh.h"

class MeshComponent : public Component {
  public:
    MeshComponent(Actor *owner);
    virtual ~MeshComponent();

    bool getVisible() const { return isVisible; }
    void setVisible(bool isVisibleP) { isVisible = isVisibleP; }

    virtual void draw();
    void setMesh(Mesh &meshP);
    void setMaterial(Material *materialP);
    void setTextureIndex(size_t textureIndexP); 

  protected:
    Material *material;
    Mesh *mesh;
    size_t textureIndex;
    bool isVisible;
};

#endif
