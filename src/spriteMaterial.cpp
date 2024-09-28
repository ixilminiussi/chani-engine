#include "spriteMaterial.h"

SpriteMaterial::SpriteMaterial() : Material()
{
    shaderName = "Sprite";
}

void SpriteMaterial::use()
{
    if (true)
    {
        selected = this;

        // Enable depth buffering, alpha blending etc
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

        Shader &shader = getShader();
        shader.setMatrix4("uViewProj", spriteViewProj);
        shader.use();
    }
}
