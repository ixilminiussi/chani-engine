#include "material.h"
#include "assets.h"
#include "log.h"

Material::Material()
    : shaderName(""), view(Matrix4::createLookAt(Vector3::zero, Vector3::unitX,
                                                 Vector3::unitZ)),
      projection(Matrix4::createPerspectiveFOV(Maths::toRadians(70.0f),
                                               WINDOW_WIDTH, WINDOW_HEIGHT,
                                               10.0f, 10000.0f)),
      spriteViewProj(
          Matrix4::createSimpleViewProj(WINDOW_WIDTH, WINDOW_HEIGHT)) {
}

Shader &Material::getShader() { return Assets::getShader(shaderName); }

Material *Material::selected = nullptr;

void Material::init() {};

void Material::use() {};
