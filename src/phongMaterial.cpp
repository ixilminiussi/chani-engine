#include "phongMaterial.h"
#include "assets.h"
#include "random.h"
#include "shader.h"
#include <chani/shader.h>

PhongMaterial::PhongMaterial() : Material()
{
    shaderName = "Phong";
}

void PhongMaterial::use()
{
    // Enable depth buffering/disable alpha blend
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    getShader().use();

    getShader().setFloat("uSpecular", specular);
    getShader().setSampler2D("uTexture", 0);
    getShader().setMatrix4f("uViewProj", view * projection);
}

Material *PhongMaterial::makeUnique()
{
    PhongMaterial *newMat = new PhongMaterial();

    newMat->view = view;
    newMat->projection = projection;
    newMat->spriteViewProj = spriteViewProj;
    newMat->specular = specular;
    newMat->shaderName = shaderName;

    Assets::loadCustomMaterial(newMat, Random::getUUID().c_str());

    return newMat;
}

void PhongMaterial::setSpecular(const float &specularP)
{
    specular = specularP;
}
