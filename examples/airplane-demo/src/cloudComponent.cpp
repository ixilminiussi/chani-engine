#include "cloudComponent.h"

#include "cloudMaterial.h"
#include <assets.h>
#include <chani.h>
#include <fstream>
#include <log.h>
#include <mesh.h>
#include <postProcessComponent.h>
#include <shader.h>
#include <sstream>

CloudComponent::CloudComponent(Actor *ownerP, Cuboid *cuboid)
    : PostProcessComponent(ownerP), perlinResolution(Vector3(100.0f, 100.0f, 100.0f))
{
    CloudMaterial *material = dynamic_cast<CloudMaterial *>(Assets::getMaterial("Material_Cloud"));
    material->setArea(cuboid);

    setMaterial(material);
}

void CloudComponent::generatePerlinNoise()
{
    glUseProgram(computeProgram);
    glDispatchCompute((int)perlinResolution.x, (int)perlinResolution.y, (int)perlinResolution.z);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

bool CloudComponent::loadCompute(const std::string &filename)
{
    std::string shaderCode;

    try
    {
        std::ifstream shaderFile(shaderCode);
        std::stringstream shaderStream;

        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    }
    catch (std::exception e)
    {
        std::ostringstream loadError;
        loadError << "ERROR::SHADER: Failed to read compute shader " << filename << "\n"
                  << "\n -- --------------------------------------------------- -- " << std::endl;

        Log::error(LogCategory::Render, loadError.str());
        return false;
    }

    const char *computeShaderSource = shaderCode.c_str();

    computeShader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(computeShader, 1, &computeShaderSource, NULL);
    glCompileShader(computeShader);

    computeProgram = glCreateProgram();
    glAttachShader(computeProgram, computeShader);
    glLinkProgram(computeProgram);

    return true;
}
