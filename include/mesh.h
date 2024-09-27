#if !defined(MESH_H)
#define MESH_H

#include "texture.h"
#include "vertexArray.h"

class Mesh
{
  public:
    Mesh();
    ~Mesh();

    void unload();

    VertexArray *getVertexArray();
    float getRadius() const;

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
