#if !defined(MATERIAL_H)
#define MATERIAL_H

#include "shader.h"
#include <string>

class Material
{
  public:
    Material();
    virtual ~Material() = default;

    virtual void use() = 0;

    virtual void unload()
    {
    }

    virtual Material *makeUnique() = 0;

    void setView(const Matrix4<float> &viewP);
    void setShaderName(const std::string &shaderNameP);
    Shader &getShader();
    void setWorldTransform(const Matrix4<float> &wt);

  protected:
    std::string shaderName;
    static Material *selected;

    Matrix4<float> view;
    Matrix4<float> projection;
    Matrix4<float> spriteViewProj;
};

#endif
