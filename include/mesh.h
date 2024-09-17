#if !defined(MESH_H)
#define MESH_H

#include "texture.h"

#include <string>
#include <vector>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void unload();

	class VertexArray* getVertexArray() { return vertexArray; }
	const std::string& getShaderName() const { return shaderName; }
	float getRadius() const { return radius; }
	float getSpecularPower() const { return specularPower; }

	void addTexture(Texture* texture);
	Texture* getTexture(int index);

	void setVertexArray(VertexArray* vertexArrayP);
	void setShaderName(const std::string& shaderNameP);
	void setRadius(float radiusP);
	void setSpecularPower(float specularPowerP);

private:
    std::vector<Texture*> textures;
	class VertexArray* vertexArray;
    std::string shaderName;
	float radius; // Bounding sphere radius
	float specularPower;
};

#endif
