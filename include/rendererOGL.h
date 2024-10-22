#include <chani/shader.h>
#if !defined(RENDERER_OGL_H)
#define RENDERER_OGL_H

#include "directionalLight.h"
#include "iRenderer.h"
#include "shader.h"
#include "vertexArray.h"

#include <vector>

class RendererOGL : public IRenderer
{
  public:
    RendererOGL();
    virtual ~RendererOGL();
    RendererOGL(const RendererOGL &) = delete;
    RendererOGL &operator=(const RendererOGL &) = delete;

    bool initialize(Window &window);
    void beginDraw();
    void draw();
    void endDraw();
    void close();
    IRenderer::Type type();

    void addSprite(class SpriteComponent *sprite);
    void removeSprite(class SpriteComponent *sprite);
    //     void drawSprite(const class Actor &actor, const class Texture &tex,
    //                   struct Rectangle srcRect, Vector2 origin, Flip flip)
    //                   const;

    void addMesh(class MeshComponent *mesh);
    void removeMesh(class MeshComponent *mesh);

    void addPostProcess(class PostProcessComponent *postProcess);
    void removePostProcess(class PostProcessComponent *postProcess);

    DirectionalLight &getDirectionalLight();

    void setViewMatrix(const Matrix4 &viewP);
    void setLightUniforms(Shader &shader);
    void setAmbientLight(const Vector3 &ambientP);
    void setClearColor(const Vector3 &colorP);

    GLuint getColorTexture() const;
    GLuint getDepthTexture() const;

  private:
    void drawMeshes();
    void drawSprites();

    bool initializeFrameBuffer();
    void drawPostProcesses();

    Window *window;
    SDL_GLContext context;
    GLuint framebuffer, colorTextureBuffer, depthTextureBuffer;
    VertexArray *spriteVertexArray;
    Vector3 clearColor;

    Matrix4 view;

    std::vector<class MeshComponent *> meshes;
    std::vector<class SpriteComponent *> sprites;
    std::vector<class PostProcessComponent *> postProcesses;

    Vector3 ambientLight;
    DirectionalLight dirLight;
};

#endif
