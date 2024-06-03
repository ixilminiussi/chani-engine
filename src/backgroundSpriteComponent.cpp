#include "../include/backgroundSpriteComponent.h"

#include "../include/actor.h"
#include "../include/log.h"

BackgroundSpriteComponent::BackgroundSpriteComponent(Actor* ownerP, std::vector<Texture*> const& texturesP, int drawOrderP) :
    SpriteComponent(ownerP, *texturesP[0], drawOrderP),
    scrollSpeed(0.f),
    screenSize(Vector2{ WINDOW_WIDTH, WINDOW_HEIGHT })
{
    setTextures(texturesP);
}

BackgroundSpriteComponent::~BackgroundSpriteComponent() {}

void BackgroundSpriteComponent::update(float dt) {
    SpriteComponent::update(dt);

    for(BGTexture& bg : textures) {
        bg.offset.x += scrollSpeed * dt;

        if (bg.offset.x < -screenSize.x) {
            bg.offset.x = (textures.size() - 1) * screenSize.x - 1;
        }
    }
}

void BackgroundSpriteComponent::draw(Renderer& renderer) {
    for (BGTexture& bg : textures) {
        owner.setPosition(Vector2(bg.offset.x, bg.offset.y));
        renderer.drawSprite(owner, bg.texture, Rectangle::nullRect, Vector2::zero, Renderer::Flip::None);
    }
}

void BackgroundSpriteComponent::setTextures(std::vector<Texture*> const& texturesP) {
    int count = 0;
    for (Texture* tex : texturesP) {
        BGTexture temp { *tex, Vector2(count * screenSize.x, 0) };
        textures.emplace_back(temp);
        count ++;
    }
}

void BackgroundSpriteComponent::setScreenSize(Vector2 const& screenSizeP) {
    screenSize = screenSizeP;
}

void BackgroundSpriteComponent::setScrollSpeed(float scrollSpeedP) {
    scrollSpeed = scrollSpeedP;
}
