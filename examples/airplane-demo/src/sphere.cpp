#include "sphere.h"

#include <assets.h>
#include <mesh.h>
#include <meshComponent.h>
#include <phongMaterial.h>

Sphere::Sphere() : Actor()
{
    mc = new MeshComponent(this);
    mc->setMaterial(dynamic_cast<PhongMaterial *>(Assets::getMaterial("Material_Phong")));
    mc->setMesh(*(Assets::getMesh("Mesh_Sphere").makeUnique()));
}

MeshComponent *Sphere::getMeshComponent() const
{
    return mc;
}
