#include "rendererOGL.h"

#include "actor.h"
#include "assets.h"
#include "log.h"
#include "meshComponent.h"
#include "rectangle.h"
#include "spriteComponent.h"

#include <algorithm>

#include <GL/glew.h>
#include <SDL_image.h>

RendererOGL::RendererOGL()
    : window(nullptr), context(nullptr), spriteVertexArray(nullptr),
      ambientLight(Vector3(1.0f, 1.0f, 1.0f)),
      dirLight({Vector3::zero, Vector3::zero, Vector3::zero}),
      clearColor(0.0f, 0.0f, 0.0f),
      view(Matrix4::createLookAt(Vector3::zero, Vector3::unitX,
                                 Vector3::unitZ)) {}

RendererOGL::~RendererOGL() {}

bool RendererOGL::initialize(Window &windowP) {
    window = &windowP;

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
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
    if (glewInit() != GLEW_OK) {
        Log::error(LogCategory::Video, "Failed to initialize GLEW.");
        return false;
    }

    // On some platforms, GLEW will emit a benign error code, so clear it
    glGetError();

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        Log::error(LogCategory::Video, "Unable to initialize SDL_image");
        return false;
    }

    spriteVertexArray = new VertexArray(spriteVertices, 4, indices, 6);
    return true;
}

void RendererOGL::beginDraw() {
    glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererOGL::draw() {
    for (auto &[shaderName, shader] : Assets::shaders) {
        setLightUniforms(shader);
    }

    drawMeshes();
    drawSprites();
}

void RendererOGL::endDraw() { SDL_GL_SwapWindow(window->getSDLWindow()); }

void RendererOGL::close() {
    delete spriteVertexArray;
    SDL_GL_DestroyContext(context);
}

void RendererOGL::drawMeshes() {
    // Draw
    for (auto mc : meshes) {
        if (mc->getVisible()) {
            mc->draw();
        }
    }
}

void RendererOGL::addSprite(SpriteComponent *sprite) {
    // Insert the sprite at the right place in function of drawOrder
    int spriteDrawOrder = sprite->getDrawOrder();
    auto iter = begin(sprites);
    for (; iter != end(sprites); ++iter) {
        if (spriteDrawOrder < (*iter)->getDrawOrder())
            break;
    }
    sprites.insert(iter, sprite);
}

void RendererOGL::removeSprite(SpriteComponent *sprite) {
    auto iter = std::find(begin(sprites), end(sprites), sprite);
    sprites.erase(iter);
}

void RendererOGL::drawSprites() {
    spriteVertexArray->setActive();

    for (auto sprite : sprites) {
        if (sprite->getVisible()) {
            sprite->draw();
        }
    }
}

// void RendererOGL::drawSprite(const Actor &actor, const Texture &tex,
//                              Rectangle srcRect, Vector2 origin,
//                              Flip flip) const {
//     Matrix4 scaleMat = Matrix4::createScale((float)tex.getWidth(),
//                                             (float)tex.getHeight(), 1.0f);
//     Matrix4 world = scaleMat * actor.getWorldTransform();
//     Assets::getShader("Sprite").setMatrix4("uWorldTransform", world);
//     tex.setActive();
//     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
// }

void RendererOGL::addMesh(MeshComponent *mesh) { meshes.emplace_back(mesh); }

void RendererOGL::removeMesh(MeshComponent *mesh) {
    auto iter = std::find(begin(meshes), end(meshes), mesh);
    meshes.erase(iter);
}

void RendererOGL::setViewMatrix(const Matrix4 &viewP) {
    view = viewP;
    for (auto &[materialName, material] : Assets::materials) {
        material->setView(view);
    }
}

void RendererOGL::setLightUniforms(Shader &shader) {
    // Camera position is from inverted view
    Matrix4 invertedView = view;
    invertedView.invert();
    shader.setVector3f("uCameraPos", invertedView.getTranslation());
    // Ambient
    shader.setVector3f("uAmbientLight", ambientLight);
    // Directional light
    shader.setVector3f("uDirLight.direction", dirLight.direction);
    shader.setVector3f("uDirLight.diffuseColor", dirLight.diffuseColor);
    shader.setVector3f("uDirLight.specColor", dirLight.specColor);
}

void RendererOGL::setAmbientLight(const Vector3 &ambientP) {
    ambientLight = ambientP;
}
