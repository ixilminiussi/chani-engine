#include "mesh.h"

#include "log.h"
#include "vertexArray.h"
#include <stdexcept>

Mesh::Mesh() : vertexArray(nullptr), radius(0.0f) {}

Mesh::~Mesh() {}

void Mesh::unload() {
    delete vertexArray;
    vertexArray = nullptr;
}

void Mesh::setVertexArray(VertexArray *vertexArrayP) {
    vertexArray = vertexArrayP;
}

Texture *Mesh::getTexture(int index) {
    Texture *texture;
    try {
        texture = textures.at(index);
        return texture;
    }
    catch (const std::out_of_range& e) {
        Log::error(LogCategory::Application, e.what());
    }

    return nullptr;
}

void Mesh::addTexture(Texture *texture) {
    textures.push_back(texture);
}

void Mesh::setRadius(const float &radiusP) { radius = radiusP; }
