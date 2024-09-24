#include "meshComponent.h"

#include "actor.h"
#include "chani.h"
#include "mesh.h"

MeshComponent::MeshComponent(Actor *owner)
    : Component(owner), mesh(nullptr), textureIndex(0), isVisible(true) {
    owner->getGame().getRenderer().addMesh(this);
}

MeshComponent::~MeshComponent() {
    owner.getGame().getRenderer().removeMesh(this);
}

void MeshComponent::draw() {
    if (mesh && material) {
        material->use();

        Matrix4 wt = owner.getWorldTransform();
        material->setWorldTransform(wt);

        Texture *t = mesh->getTexture(textureIndex);
        if (t) {
            t->setActive();
        }

        VertexArray *va = mesh->getVertexArray();
        va->setActive();

        glDrawElements(GL_TRIANGLES, va->getNbIndices(), GL_UNSIGNED_INT,
                       nullptr);
    }
}

void MeshComponent::setMesh(Mesh &meshP) { mesh = &meshP; }

void MeshComponent::setMaterial(Material *materialP) { material = materialP; }

void MeshComponent::setTextureIndex(size_t textureIndexP) {
    textureIndex = textureIndexP;
}
