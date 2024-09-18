#if !defined(MESH_COMPONENT_H)
#define MESH_COMPONENT_H

#include "component.h"

class MeshComponent : public Component {
  public:
    MeshComponent(Actor *owner);
    virtual ~MeshComponent();

    bool getVisible() const { return isVisible; }
    void setVisible(bool isVisibleP);

    virtual void draw(class Shader &shader);
    virtual void setMesh(class Mesh &meshP);
    void setTextureIndex(size_t textureIndexP);

  protected:
    Mesh *mesh;
    size_t textureIndex;
    bool isVisible;
};

#endif
