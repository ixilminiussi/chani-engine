#if !defined(BACKGROUND_SPRITE_COMPONENT_H)
#define BACKGROUND_SPRITE_COMPONENT_H

#include "spriteComponent.h"
#include <vector>

class BackgroundSpriteComponent : public SpriteComponent {
public:
    BackgroundSpriteComponent(Actor* ownerP, std::vector<Texture*> const& texturesP, int drawOrderP = 10);
    virtual ~BackgroundSpriteComponent();
    BackgroundSpriteComponent() = delete;
    BackgroundSpriteComponent(BackgroundSpriteComponent const&) = delete;
    BackgroundSpriteComponent& operator=(BackgroundSpriteComponent const&) = delete;

    float getScrollSpeed() const { return scrollSpeed; }
    void setTextures(std::vector<Texture*> const&);
    void setScreenSize(Vector2 const& screenSizeP);
    void setScrollSpeed(float scrollSpeedP);

    void update(float dt) override;
    void draw(Renderer& renderer) override;

private:
    struct BGTexture {
        BGTexture(Texture& t, Vector2 o) : texture(t), offset(o) {}
        Texture& texture;
        Vector2 offset;
    };
    std::vector<BGTexture> textures;
    Vector2 screenSize;
    float scrollSpeed;
};

#endif
