#include "sphere.h"

#include <assets.h>
#include <meshComponent.h>

Sphere::Sphere() : Actor() {
    mc = new MeshComponent(this);
    mc->setMesh(Assets::getMesh("Mesh_Sphere"));
}
