#include "meshComponent.h"

#include "actor.h"
#include "chani.h"
#include "mesh.h"

MeshComponent::MeshComponent(Actor *owner) : Component(owner), mesh(nullptr), textureIndex(0), isVisible(true)
{
    owner->getGame().getRenderer().addMesh(this);
}

MeshComponent::~MeshComponent()
{
    owner.getGame().getRenderer().removeMesh(this);
}

bool MeshComponent::getVisible() const
{
    return isVisible;
}

void MeshComponent::setVisible(bool isVisibleP)
{
    isVisible = isVisibleP;
}

void MeshComponent::draw()
{
    if (material)
    {
        material->use();
        material->setWorldTransform(owner.getWorldTransform());

        Texture *t = mesh->getTexture(textureIndex);
        if (t)
        {
            t->setActive();
        }

        VertexArray *va = mesh->getVertexArray();
        va->setActive();

        glDrawElements(GL_TRIANGLES, va->getNbIndices(), GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        // TODO: Throw error
    }
}

void MeshComponent::setMesh(Mesh &meshP)
{
    mesh = &meshP;
}

void MeshComponent::setMaterial(Material *materialP)
{
    material = materialP;
}

void MeshComponent::setTextureIndex(size_t textureIndexP)
{
    textureIndex = textureIndexP;
}

// TODO: ADD DEBUGGING FUNCTIONS / VARIABLE TO DEBUG SPECIFIC ACTOR
