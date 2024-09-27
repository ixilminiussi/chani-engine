#include "pbrMaterial.h"
#include "shader.h"

PBRMaterial::PBRMaterial() : Material()
{
    shaderName = "PBR";
}

void PBRMaterial::use()
{
    if (selected != this)
    {
        selected = this;

        // Enable depth buffering/disable alpha blend
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
        Shader &shader = getShader();
        shader.use();

        shader.setFloat("uRoughness", roughness);
        shader.setMatrix4("uViewProj", view * projection);
    }
}

void PBRMaterial::setRoughness(const float &roughnessP)
{
    roughness = roughnessP;
}
