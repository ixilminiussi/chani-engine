#include "plane.h"

#include "assets.h"
#include "meshComponent.h"

Plane::Plane() : Actor() {
    setScale(10.0f);
    MeshComponent *mc = new MeshComponent(this);
    mc->setMesh(Assets::getMesh("Mesh_Plane"));
}
