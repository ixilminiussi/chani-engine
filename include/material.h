#if !defined(MATERIAL_H)
#define MATERIAL_H

#include "shader.h"
#include <string>

class Material {
  public:
    Material();
    ~Material() = default;

    virtual void use();
    virtual void init();

    void setView(const Matrix4 &viewP) { view = viewP; }
    void setShaderName(const std::string &shaderNameP) {
        shaderName = shaderNameP;
    }
    Shader &getShader();

  protected:
    std::string shaderName;
    static Material *selected;

    Matrix4 view;
    Matrix4 projection;
    Matrix4 spriteViewProj;
};

#endif
