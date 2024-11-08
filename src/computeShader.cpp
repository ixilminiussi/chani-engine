#include "computeShader.h"
#include "assets.h"
#include "log.h"

ComputeShader &ComputeShader::use()
{
    glUseProgram(id);
    return *this;
}

void ComputeShader::compile(const GLchar *source)
{
    compileComputeShader(source);
    createShaderProgram();
}

void ComputeShader::reload()
{
    Assets::loadComputeShader(filePath, name);
}

void ComputeShader::unload()
{
    glDeleteProgram(id);
}

void ComputeShader::compileComputeShader(const GLchar *source)
{
    cs = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(cs, 1, &source, nullptr);
    glCompileShader(cs);
    // checkShaderErrors(vs, "compute");
}

void ComputeShader::createShaderProgram()
{
    // Create program
    id = glCreateProgram();
    glAttachShader(id, cs);
    glLinkProgram(id);

    // Check for linking error
    int params = -1;
    glGetProgramiv(id, GL_LINK_STATUS, &params);
    if (params != GL_TRUE)
    {
        Log::error(LogCategory::Error, "Could not link compute shader programme");
    }
    glValidateProgram(id);
    glGetProgramiv(id, GL_VALIDATE_STATUS, &params);
    if (params != GL_TRUE)
    {
        Log::error(LogCategory::Error, "Could not validate compute shader programme");
    }

    // Delete shaders for they are no longer used
    glDeleteShader(cs);
}

void ComputeShader::setFloat(const GLchar *name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(id, name), value);
}
void ComputeShader::setInteger(const GLchar *name, GLint value)
{
    glUniform1i(glGetUniformLocation(id, name), value);
}
void ComputeShader::setSampler2D(const GLchar *name, GLint value)
{
    glUniform1i(glGetUniformLocation(id, name), value);
}
void ComputeShader::setVector2f(const GLchar *name, GLfloat x, GLfloat y)
{
    glUniform2f(glGetUniformLocation(id, name), x, y);
}
void ComputeShader::setVector2f(const GLchar *name, const Vector2 &value)
{
    glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}
void ComputeShader::setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z)
{
    glUniform3f(glGetUniformLocation(id, name), x, y, z);
}
void ComputeShader::setVector3f(const GLchar *name, const Vector3 &value)
{
    glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}

void ComputeShader::setFilePath(const std::string &filePathP)
{
    filePath = filePathP;
}

void ComputeShader::setName(const std::string &nameP)
{
    name = nameP;
}
