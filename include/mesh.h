#if !defined(MESH_H)
#define MESH_H

#include "texture.h"

class Mesh {
  public:
    Mesh();
    ~Mesh();

    void unload();

    class VertexArray *getVertexArray() { return vertexArray; }
    float getRadius() const { return radius; }

    void setVertexArray(VertexArray *vertexArrayP);
    void setRadius(const float &radiusP);

    Texture *getTexture(int index);
    void addTexture(Texture *texture);

  private:
    std::vector<Texture *> textures;
    class VertexArray *vertexArray;
    float radius; // Bounding sphere radius
};

#endif
