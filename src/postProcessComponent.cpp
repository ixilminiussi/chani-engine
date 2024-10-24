#include "postProcessComponent.h"

#include "actor.h"
#include "chani.h"
#include "component.h"
#include "texture.h"
#include <chani/shader.h>

PostProcessComponent::PostProcessComponent(Actor *owner)
    : Component(owner), textureIndex(0), isVisible(true) {
    owner->getGame().getRenderer().addPostProcess(this);
    initQuad();
}

PostProcessComponent::~PostProcessComponent() {
    owner.getGame().getRenderer().removePostProcess(this);
}

bool PostProcessComponent::getVisible() const { return isVisible; }

void PostProcessComponent::setVisible(bool isVisibleP) {
    isVisible = isVisibleP;
}

void PostProcessComponent::draw() const {
    if (material) {
        material->use();
        material->setWorldTransform(owner.getWorldTransform());
    }

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void PostProcessComponent::setMaterial(Material *materialP) {
    material = materialP;
}

void PostProcessComponent::initQuad() {
    // Fullscreen quad vertices
    float quadVertices[] = {
        -1.0f, 1.0f,  0.0f, 1.0f, // Top-left
        -1.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
        1.0f,  -1.0f, 1.0f, 0.0f, // Bottom-right
        1.0f,  1.0f,  1.0f, 1.0f  // Top-right
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices,
                 GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    // TexCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
