#include "material.h"
#include "assets.h"
#include "rendererOGL.h"

Material::Material()
    : shaderName(""),
      view(Matrix4<float>::createLookAt(Vector3<float>::zero(), Vector3<float>::unitX(), Vector3<float>::unitZ())),
      projection(Matrix4<float>::createPerspectiveFOV(Maths::toRadians(70.0f), WINDOW_WIDTH, WINDOW_HEIGHT,
                                                      RendererOGL::nearPlane, RendererOGL::farPlane)),
      spriteViewProj(Matrix4<float>::createSimpleViewProj(WINDOW_WIDTH, WINDOW_HEIGHT))
{
}

void Material::setView(const Matrix4<float> &viewP)
{
    view = viewP;
}

void Material::setShaderName(const std::string &shaderNameP)
{
    shaderName = shaderNameP;
}

Shader &Material::getShader()
{
    return Assets::getShader(shaderName);
}

void Material::setWorldTransform(const Matrix4<float> &wt)
{
    getShader().use();
    getShader().setMatrix4f("uWorldTransform", wt);
}

Material *Material::selected = nullptr;
