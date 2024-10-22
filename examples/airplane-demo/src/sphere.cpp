#include "sphere.h"

#include <assets.h>
#include <mesh.h>
#include <meshComponent.h>

Sphere::Sphere() : Actor()
{
    mc = new MeshComponent(this);
    mc->setMesh(*(Assets::getMesh("Mesh_Sphere").makeUnique()));
}

MeshComponent *Sphere::getMeshComponent() const
{
    return mc;
}
