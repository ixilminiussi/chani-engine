#if !defined(SHADER_H)
#define SHADER_H

#include "matrix4.h"
#include "vector2.h"

// clang-format off
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
// clang-format on

#include <string>

// General purpose shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility
// functions for easy management.
class Shader
{
  public:
    // State
    GLuint id;

    // Constructor
    Shader() : id(0), vs(0), fs(0), gs(0), tcs(0), tes(0)
    {
    }

    // Unload the shader
    void unload();

    // Sets the current shader as active
    Shader &use();

    // Compiles the shader from given source code
    void compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *tessControlSource = nullptr,
                 const GLchar *tessEvalSource = nullptr, const GLchar *geometrySource = nullptr);

    // Utility functions
    void setFloat(const GLchar *name, GLfloat value);
    void setInteger(const GLchar *name, GLint value);
    void setVector2f(const GLchar *name, GLfloat x, GLfloat y);
    void setVector2f(const GLchar *name, const Vector2<float> &value);
    void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
    void setVector3f(const GLchar *name, const Vector3<float> &value);
    void setSampler2D(const GLchar *name, GLint value);
    void setSampler3D(const GLchar *name, GLint value);
    void setBufferObject(const GLchar *name, GLint value);
    /*
    void setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z,
    GLfloat w); void setVector4f(const GLchar* name, const Vector4& value);
    */
    void setMatrix4f(const GLchar *name, const Matrix4<float> &matrix);

  protected:
    GLuint vs;
    GLuint fs;
    GLuint tcs;
    GLuint tes;
    GLuint gs;

    void compileVertexShader(const GLchar *vertexSource);
    void compileFragmentShader(const GLchar *fragmentSource);
    bool compileTessControlShader(const GLchar *tessControlSource);
    bool compileTessEvalShader(const GLchar *tessEvalSource);
    bool compileGeometryShader(const GLchar *geometrySource);
    void createShaderProgram(bool tessShadersExist, bool geometryShaderExists);

    void checkShaderErrors(GLuint shader, std::string shaderType);
    void printShaderInfoLog(GLuint shaderIndex);
    void printProgrammeInfoLog(GLuint programme);
    const char *GLTypeToString(GLenum type);
    void printAllParams(GLuint programme);
    bool isValid(GLuint programme);
};

#endif
