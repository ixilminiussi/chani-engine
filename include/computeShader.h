#ifndef COMPUTE_SHADER_H
#define COMPUTE_SHADER_H

// clang-format off
#include "vector2.h"
#include "vector3.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
// clang-format on

class ComputeShader
{
  public:
    // Program id
    GLuint id;

    // Constructor
    ComputeShader() = default;

    // Sets the current shader as active
    ComputeShader &use();

    // Compiles the shader from given source code
    void reload();
    void compile(const GLchar *source);

    void setFloat(const GLchar *name, GLfloat value);
    void setInteger(const GLchar *name, GLint value);
    void setUnsigned(const GLchar *name, GLuint value);
    void setVector2f(const GLchar *name, GLfloat x, GLfloat y);
    void setVector2f(const GLchar *name, const Vector2<float> &value);
    void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
    void setVector3f(const GLchar *name, const Vector3<float> &value);
    void setVector2ui(const GLchar *name, GLuint x, GLuint y);
    void setVector2ui(const GLchar *name, const Vector2<uint> &value);
    void setVector3ui(const GLchar *name, GLuint x, GLuint y, GLuint z);
    void setVector3ui(const GLchar *name, const Vector3<uint> &value);
    void setSampler2D(const GLchar *name, GLint value);
    void setSampler3D(const GLchar *name, GLint value);

    void unload();

    void setFilePath(const std::string &filePath);
    void setName(const std::string &name);

  private:
    GLuint cs;
    std::string filePath, name;

    void compileComputeShader(const GLchar *cSource);
    void createShaderProgram();
};

#endif
