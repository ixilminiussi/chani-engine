#if !defined(SPRITE_COMPONENT_H)
#define SPRITE_COMPONENT_H

#include "component.h"
#include "material.h"
#include "texture.h"

class SpriteComponent : public Component
{
  public:
    SpriteComponent(Actor *ownerP, Texture &textureP,
                    int drawOrderP = 100); // Lower draw order: further back
    virtual ~SpriteComponent();
    SpriteComponent() = delete;
    SpriteComponent(const SpriteComponent &) = delete;
    SpriteComponent &operator=(const SpriteComponent &) = delete;

    virtual void setTexture(const Texture &textureP);
    void setMaterial(Material *materialP);

    virtual void draw();

    int getDrawOrder() const;
    int getTexWidth() const;
    int getTexHeight() const;
    bool getVisible() const;

    void setVisible(bool isVisibleP);

  protected:
    Texture texture;
    Material *material;
    int drawOrder;
    int texWidth;
    int texHeight;
    bool isVisible;
};

#endif
