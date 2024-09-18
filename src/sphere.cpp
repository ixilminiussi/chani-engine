#include "sphere.h"

#include "assets.h"
#include "meshComponent.h"

Sphere::Sphere() : Actor() {
    MeshComponent *mc = new MeshComponent(this);
    mc->setMesh(Assets::getMesh("Mesh_Sphere"));
}
