#include "phongMaterial.h"
#include "shader.h"

PhongMaterial::PhongMaterial() : Material()
{
    shaderName = "Phong";
}

void PhongMaterial::use()
{
    if (true)
    {
        selected = this;

        // Enable depth buffering/disable alpha blend
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

        Shader &shader = getShader();
        shader.setFloat("uSpecular", specular);
        shader.setMatrix4("uViewProj", view * projection);

        shader.use();
    }
}

void PhongMaterial::setSpecular(const float &specularP)
{
    specular = specularP;
}
