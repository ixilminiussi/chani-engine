#include "cube.h"

#include "assets.h"
#include "meshComponent.h"

Cube::Cube() {
    MeshComponent *mc = new MeshComponent(this);
    mc->setMesh(Assets::getMesh("Mesh_Cube"));
}
