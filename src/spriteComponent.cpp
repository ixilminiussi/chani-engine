#include "spriteComponent.h"

#include "actor.h"
#include "chani.h"
#include "rectangle.h"
#include "shader.h"

SpriteComponent::SpriteComponent(Actor *ownerP, Texture &textureP,
                                 int drawOrderP)
    : Component(ownerP), texture(textureP), drawOrder(drawOrderP),
      texWidth(textureP.getWidth()), texHeight(textureP.getHeight()),
      isVisible(true) {
    owner.getGame().getRenderer().addSprite(this);
}

SpriteComponent::~SpriteComponent() {
    owner.getGame().getRenderer().removeSprite(this);
}

void SpriteComponent::setTexture(const Texture &textureP) {
    texture = textureP;
    texture.updateInfo(texWidth, texHeight);
}

void SpriteComponent::draw() {
    Vector2 origin{texWidth / 2.f, texHeight / 2.f};
    Matrix4 scaleMat = Matrix4::createScale((float)texture.getWidth(),
                                            (float)texture.getHeight(), 1.0f);
    Matrix4 world = scaleMat * owner.getWorldTransform();
    material.getShader().setMatrix4("uWorldTransform", world);
    texture.setActive();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void SpriteComponent::setVisible(bool isVisibleP) { isVisible = isVisibleP; }
