#include "material.h"
#include "assets.h"

Material::Material()
    : shaderName(""), view(Matrix4::createLookAt(Vector3::zero, Vector3::unitX, Vector3::unitZ)),
      projection(Matrix4::createPerspectiveFOV(Maths::toRadians(70.0f), WINDOW_WIDTH, WINDOW_HEIGHT, 10.0f, 10000.0f)),
      spriteViewProj(Matrix4::createSimpleViewProj(WINDOW_WIDTH, WINDOW_HEIGHT))
{
}

void Material::setView(const Matrix4 &viewP)
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

void Material::setWorldTransform(const Matrix4 &wt)
{
    getShader().setMatrix4("uWorldTransform", wt);
}

Material *Material::selected = nullptr;
