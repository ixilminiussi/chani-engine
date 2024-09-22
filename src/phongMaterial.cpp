#include "phongMaterial.h"
#include "shader.h"

PhongMaterial::PhongMaterial() : Material() { shaderName = "Phong"; }

void PhongMaterial::use() {
    if (selected != this) {
        selected = this;

        // Enable depth buffering/disable alpha blend
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
        Shader &shader = getShader();
        shader.setMatrix4("uViewProj", view * projection);
        shader.use();
    }
}

void PhongMaterial::init() {
    getShader().setFloat("uSpecPower", specular);
}