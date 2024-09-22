#include "mesh.h"

#include "vertexArray.h"

Mesh::Mesh() : vertexArray(nullptr), radius(0.0f) {}

Mesh::~Mesh() {}

void Mesh::unload() {
    delete vertexArray;
    vertexArray = nullptr;
}

void Mesh::setVertexArray(VertexArray *vertexArrayP) {
    vertexArray = vertexArrayP;
}

void Mesh::setRadius(const float &radiusP) { radius = radiusP; }
