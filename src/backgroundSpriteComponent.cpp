#include "backgroundSpriteComponent.h"

#include "actor.h"
#include "shader.h"

BackgroundSpriteComponent::BackgroundSpriteComponent(Actor *ownerP, const std::vector<Texture *> &texturesP,
                                                     int drawOrderP)
    : SpriteComponent(ownerP, *texturesP[0], drawOrderP), scrollSpeed(0.0f),
      screenSize(Vector2(WINDOW_WIDTH, WINDOW_HEIGHT))
{
    setTextures(texturesP);
}

BackgroundSpriteComponent::~BackgroundSpriteComponent()
{
}

void BackgroundSpriteComponent::update(float dt)
{
    SpriteComponent::update(dt);
    for (auto &bg : textures)
    {
        bg.offset.x += scrollSpeed * dt;
        // If this is completely off the screen, reset offset to
        // the right of the last bg texture
        if (bg.offset.x < -screenSize.x)
        {
            bg.offset.x = (textures.size() - 1) * screenSize.x - 1;
        }
    }
}

void BackgroundSpriteComponent::draw()
{
    // Draw each background texture
    if (material)
    {
        for (auto &bg : textures)
        {
            owner.setPosition(Vector3(0.0f, bg.offset.x, bg.offset.y));
            Matrix4<float> scaleMat =
                Matrix4<float>::createScale((float)texture.getWidth(), (float)texture.getHeight(), 1.0f);

            Matrix4<float> world = scaleMat * owner.getWorldTransform();
            material->use();
            material->setWorldTransform(world);

            texture.setActive();

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        }
    }
    else
    {
        // TODO: Throw error
    }
}

float BackgroundSpriteComponent::getScrollSpeed() const
{
    return scrollSpeed;
}

void BackgroundSpriteComponent::setTextures(const std::vector<Texture *> &texturesP)
{
    int count = 0;
    for (auto tex : texturesP)
    {
        BGTexture temp{*tex, Vector2<float>(count * screenSize.x, 0)}; // Each texture is screen width in offset
        textures.emplace_back(temp);
        count++;
    }
}

void BackgroundSpriteComponent::setScreenSize(const Vector2<int> &screenSizeP)
{
    screenSize = screenSizeP;
}

void BackgroundSpriteComponent::setScrollSpeed(float scrollSpeedP)
{
    scrollSpeed = scrollSpeedP;
}
