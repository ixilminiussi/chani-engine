#include "rendererOGL.h"

#include "assets.h"
#include "directionalLight.h"
#include "iRenderer.h"
#include "log.h"
#include "meshComponent.h"
#include "postProcessComponent.h"
#include "spriteComponent.h"
#include "window.h"

#include <algorithm>

#include <GL/glew.h>
#include <SDL_image.h>

float RendererOGL::nearPlane = 10.0f;
float RendererOGL::farPlane = 2000.0f;
float RendererOGL::FOV = 70.0f;

RendererOGL::RendererOGL()
    : window(nullptr), context(nullptr), spriteVertexArray(nullptr), ambientLight(Vector3<float>(1.0f, 1.0f, 1.0f)),
      dirLight({Vector3<float>::zero(), Vector3<float>::zero(), Vector3<float>::zero()}), clearColor(0.0f, 0.0f, 0.0f),
      view(Matrix4<float>::createLookAt(Vector3<float>::zero(), Vector3<float>::unitX(), Vector3<float>::unitZ())),
      framebuffer(0)
{
}

RendererOGL::~RendererOGL()
{
}

bool RendererOGL::initializeFrameBuffer()
{
    // generating and binding buffer
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // creating color texture to bind to
    glGenTextures(1, &colorTexture);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    // setting texture scale settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

    // creating depth texture to bind to
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                 nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

    // Check if the framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Log::error(LogCategory::Render, "Framebuffer is not complete");
        return false;
    }

    return true;
}

bool RendererOGL::initialize(Window &windowP)
{
    window = &windowP;

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // Request a color buffer with 8-bits per RGBA channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // Depth buffering
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Force OpenGL to use hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    // OpenGL Context
    context = SDL_GL_CreateContext(windowP.getSDLWindow());

    // GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        Log::error(LogCategory::Video, "Failed to initialize GLEW.");
        return false;
    }

    // On some platforms, GLEW will emit a benign error code, so clear it
    glGetError();

    glDepthMask(GL_TRUE);

    // Initialize Frame Buffer to render into, to allow for post processing
    if (!initializeFrameBuffer())
    {
        Log::error(LogCategory::Render, "Unable to initialize frame buffer");
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        Log::error(LogCategory::Video, "Unable to initialize SDL_image");
        return false;
    }

    spriteVertexArray = new VertexArray(spriteVertices, 4, indices, 6);
    return true;
}

void RendererOGL::beginDraw()
{
    glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);

    // to not force the need for a pass through shader, if there are no post
    // processes, simply render directly to the default buffer
    if (postProcesses.size() > 0)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    }
    else
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererOGL::draw()
{
    for (auto &[shaderName, shader] : Assets::shaders)
    {
        setLightUniforms(shader);
    }

    drawMeshes();
    drawSprites();

    if (postProcesses.size() > 0)
    {
        drawPostProcesses();
    }
}

void RendererOGL::endDraw()
{
    SDL_GL_SwapWindow(window->getSDLWindow());
}

void RendererOGL::close()
{
    delete spriteVertexArray;
    SDL_GL_DestroyContext(context);
}

IRenderer::Type RendererOGL::type()
{
    return Type::OGL;
}

void RendererOGL::drawMeshes()
{
    // Draw
    for (auto mc : meshes)
    {
        if (mc->getVisible())
        {
            mc->draw();
        }
    }
}

void RendererOGL::addSprite(SpriteComponent *sprite)
{
    // Insert the sprite at the right place in function of drawOrder
    int spriteDrawOrder = sprite->getDrawOrder();
    auto iter = begin(sprites);
    for (; iter != end(sprites); ++iter)
    {
        if (spriteDrawOrder < (*iter)->getDrawOrder())
            break;
    }
    sprites.insert(iter, sprite);
}

void RendererOGL::removeSprite(SpriteComponent *sprite)
{
    auto iter = std::find(begin(sprites), end(sprites), sprite);
    sprites.erase(iter);
}

void RendererOGL::drawSprites()
{
    spriteVertexArray->setActive();

    for (auto sprite : sprites)
    {
        if (sprite->getVisible())
        {
            sprite->draw();
        }
    }
}

// void RendererOGL::drawSprite(const Actor &actor, const Texture &tex,
//                              Rectangle srcRect, Vector2 origin,
//                              Flip flip) const {
//     Matrix4<float> scaleMat =
//     Matrix4<float>::createScale((float)tex.getWidth(),
//                                             (float)tex.getHeight(), 1.0f);
//     Matrix4<float> world = scaleMat * actor.getWorldTransform();
//     Assets::getShader("Sprite").setMatrix4<float>("uWorldTransform", world);
//     tex.setActive();
//     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
// }

void RendererOGL::addMesh(MeshComponent *mesh)
{
    meshes.emplace_back(mesh);
}

void RendererOGL::removeMesh(MeshComponent *mesh)
{
    auto iter = std::find(begin(meshes), end(meshes), mesh);
    meshes.erase(iter);
}

void RendererOGL::drawPostProcesses()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Switch back to default framebuffer
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, colorTexture);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, depthTexture);

    for (auto postProcess : postProcesses)
    {
        if (postProcess->getVisible())
        {
            postProcess->draw();
        }
    }
}

void RendererOGL::addPostProcess(PostProcessComponent *postProcess)
{
    postProcesses.emplace_back(postProcess);
}

void RendererOGL::removePostProcess(PostProcessComponent *postProcess)
{
    auto iter = std::find(begin(postProcesses), end(postProcesses), postProcess);
    postProcesses.erase(iter);
}

DirectionalLight &RendererOGL::getDirectionalLight()
{
    return dirLight;
}

void RendererOGL::setViewMatrix(const Matrix4<float> &viewP)
{
    view = viewP;
    for (auto &[materialName, material] : Assets::materials)
    {
        material->setView(view);
    }
}

void RendererOGL::setLightUniforms(Shader &shader)
{
    shader.use();
    // Camera position is from inverted view
    Matrix4<float> invertedView = view;
    invertedView.invert();
    shader.setVector3f("uCameraPos", invertedView.getTranslation());
    // Ambient
    shader.setVector3f("uAmbientLight", ambientLight);
    // Directional light
    shader.setVector3f("uDirLight.direction", dirLight.direction);
    shader.setVector3f("uDirLight.diffuseColor", dirLight.diffuseColor);
    shader.setVector3f("uDirLight.specColor", dirLight.specColor);
}

void RendererOGL::setAmbientLight(const Vector3<float> &ambientP)
{
    ambientLight = ambientP;
}

void RendererOGL::setClearColor(const Vector3<float> &color)
{
    clearColor = color;
}
