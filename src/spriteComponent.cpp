#include "spriteComponent.h"

#include "actor.h"
#include "chani.h"
#include "shader.h"

SpriteComponent::SpriteComponent(Actor *ownerP, Texture &textureP, int drawOrderP)
    : Component(ownerP), texture(textureP), drawOrder(drawOrderP), texWidth(textureP.getWidth()),
      texHeight(textureP.getHeight()), isVisible(true)
{
    owner.getGame().getRenderer().addSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    owner.getGame().getRenderer().removeSprite(this);
}

void SpriteComponent::setTexture(const Texture &textureP)
{
    texture = textureP;
    texture.updateInfo(texWidth, texHeight);
}

void SpriteComponent::setMaterial(Material *materialP)
{
    material = materialP;
}

void SpriteComponent::draw()
{
    if (material)
    {
        Vector2 origin{texWidth / 2.f, texHeight / 2.f};

        Matrix4<float> scaleMat =
            Matrix4<float>::createScale((float)texture.getWidth(), (float)texture.getHeight(), 1.0f);
        Matrix4<float> world = scaleMat * owner.getWorldTransform();
        material->use();
        material->setWorldTransform(world);

        texture.setActive();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        // TODO: Throw error if missing material
    }
}

int SpriteComponent::getDrawOrder() const
{
    return drawOrder;
}

int SpriteComponent::getTexWidth() const
{
    return texWidth;
}

int SpriteComponent::getTexHeight() const
{
    return texHeight;
}

bool SpriteComponent::getVisible() const
{
    return isVisible;
}

void SpriteComponent::setVisible(bool isVisibleP)
{
    isVisible = isVisibleP;
}
