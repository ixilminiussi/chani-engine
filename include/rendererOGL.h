#if !defined(RENDERER_OGL_H)
#define RENDERER_OGL_H

#include "iRenderer.h"
#include "vertexArray.h"
#include "vector2.h"
#include "shader.h"
#include "directionalLight.h"
#include <vector>

class RendererOGL : public IRenderer
{
public:
	RendererOGL();
	virtual ~RendererOGL();
	RendererOGL(const RendererOGL&) = delete;
	RendererOGL& operator=(const RendererOGL&) = delete;

	bool initialize(Window& window);
	void beginDraw();
	void draw();
	void endDraw();
	void close();
	IRenderer::Type type() { return Type::OGL; }

	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void drawSprite(const Actor& actor, const class Texture& tex, struct Rectangle srcRect, Vector2 origin, Flip flip) const;

	void addMesh(class MeshComponent* mesh);
	void removeMesh(class MeshComponent* mesh);

	DirectionalLight& getDirectionalLight() { return dirLight; }

	void setViewMatrix(const Matrix4& viewP);
	void setLightUniforms(Shader& shader);
	void setAmbientLight(const Vector3& ambientP);

private:
	void drawMeshes();
	void drawSprites();

	Window* window;
	SDL_GLContext context;
	VertexArray* spriteVertexArray;
	Matrix4 spriteViewProj;
	Matrix4 view;
	Matrix4 projection;

	std::vector<class MeshComponent*> meshes;
	std::vector<class SpriteComponent*> sprites;

	Vector3 ambientLight;
	DirectionalLight dirLight;
};

#endif
