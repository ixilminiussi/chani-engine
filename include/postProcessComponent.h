#include <chani/shader.h>
#if !defined(POST_PROCESS_COMPONENT_H)
#define POST_PROCESS_COMPONENT_H

#include "component.h"
#include "material.h"

class PostProcessComponent : public Component
{
  public:
    PostProcessComponent(Actor *owner);
    virtual ~PostProcessComponent();

    bool getVisible() const;
    void setVisible(bool isVisibleP);

    virtual void draw() const;
    void setMaterial(Material *materialP);
    void setTextureIndex(size_t textureIndexP);

  protected:
    void initQuad();

    GLuint quadVAO, quadVBO;

    Material *material;
    size_t textureIndex;
    bool isVisible;
};

#endif
