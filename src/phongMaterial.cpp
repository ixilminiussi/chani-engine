#include "phongMaterial.h"
#include "shader.h"

PhongMaterial::PhongMaterial() : Material()
{
    shaderName = "Phong";
}

void PhongMaterial::use()
{
    getShader().use();

    getShader().setFloat("uSpecular", specular);
    getShader().setMatrix4("uViewProj", view * projection);

    // Enable depth buffering/disable alpha blend
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}

Material *PhongMaterial::makeUnique()
{
    PhongMaterial *newMat = new PhongMaterial();

    newMat->view = view;
    newMat->projection = projection;
    newMat->spriteViewProj = spriteViewProj;
    newMat->shaderName = shaderName;
    newMat->specular = specular;

    return newMat;
}

void PhongMaterial::setSpecular(const float &specularP)
{
    specular = specularP;
}
