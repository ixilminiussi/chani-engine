#if !defined(MATERIAL_H)
#define MATERIAL_H

#include "shader.h"
#include <string>

class Material
{
  public:
    Material();
    virtual ~Material() = default;

    virtual void use();

    virtual void unload()
    {
    }

    void setView(const Matrix4 &viewP);
    void setShaderName(const std::string &shaderNameP);
    Shader &getShader();
    void setWorldTransform(const Matrix4 &wt);

  protected:
    std::string shaderName;
    static Material *selected;

    Matrix4 view;
    Matrix4 projection;
    Matrix4 spriteViewProj;
};

#endif
