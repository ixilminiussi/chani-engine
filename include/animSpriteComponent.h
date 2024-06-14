#if !defined(ANIM_SPRITE_COMPONENT_H)
#define ANIM_SPRITE_COMPONENT_H

#include "spriteComponent.h"
#include <vector>

class AnimSpriteComponent :	public SpriteComponent
{
public:
	AnimSpriteComponent(Actor* ownerP, const std::vector<Texture*>& textureP, int drawOrderP = 100);
	virtual ~AnimSpriteComponent();
	AnimSpriteComponent() = delete;
	AnimSpriteComponent(const AnimSpriteComponent&) = delete;
	AnimSpriteComponent& operator=(const AnimSpriteComponent&) = delete;

	float getAnimFPS() const { return animFPS; }
	void setAnimTextures(const std::vector<Texture*>& textures);
	void setAnimFPS(float animFPSP);

	void update(float dt) override;


private:
    std::vector<Texture*> animTextures;
	float currentFrame;
	float animFPS;
};

#endif
