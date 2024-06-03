#if !defined(ANIM_SPRITE_COMPONENT_H)
#define ANIM_SPRITE_COMPONENT_H

#include <vector>
#include "spriteComponent.h"

class AnimSpriteComponent : public SpriteComponent {
public:
    AnimSpriteComponent(Actor* ownerP, std::vector<Texture*> const& textureP, int drawOrderP = 100);
    virtual ~AnimSpriteComponent();
    AnimSpriteComponent() = delete;
    AnimSpriteComponent(AnimSpriteComponent const&) = delete;
    AnimSpriteComponent& operator=(AnimSpriteComponent const&) = delete;

    float getAnimFPS() const { return animFPS; }
    void setAnimTextures(std::vector<Texture*> const& textures);
    void setAnimFPS(float animFPSP);

    void update(float dt) override;

private:
    std::vector<Texture*> animTextures;
    float currentFrame;
    float animFPS;
};

#endif
