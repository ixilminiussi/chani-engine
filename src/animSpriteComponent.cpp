#include "animSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor *ownerP, const std::vector<Texture *> &textureP, int drawOrderP)
    : SpriteComponent(ownerP, *textureP[0], drawOrderP), currentFrame(0.0f), animFPS(24.0f)
{
    setAnimTextures(textureP);
}

AnimSpriteComponent::~AnimSpriteComponent()
{
}

void AnimSpriteComponent::setAnimTextures(const std::vector<Texture *> &texturesP)
{
    animTextures = texturesP;
    if (animTextures.size() > 0)
    {
        currentFrame = 0.f;
        setTexture(*animTextures[0]);
    }
}

float AnimSpriteComponent::getAnimFPS() const
{
    return animFPS;
}

void AnimSpriteComponent::setAnimFPS(float animFPSP)
{
    animFPS = animFPSP;
}

void AnimSpriteComponent::update(float dt)
{
    SpriteComponent::update(dt);

    if (animTextures.size() > 0)
    {
        currentFrame += animFPS * dt;
        while (currentFrame >= animTextures.size())
        {
            currentFrame -= animTextures.size();
        }
        setTexture(*animTextures[static_cast<int>(currentFrame)]);
    }
}
