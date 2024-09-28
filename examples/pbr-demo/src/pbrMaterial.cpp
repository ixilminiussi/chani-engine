#include "pbrMaterial.h"

#include <fstream>
#include <iostream>
#include <log.h>
#include <rapidjson/document.h>
#include <shader.h>
#include <sstream>

PBRMaterial::PBRMaterial() : Material()
{
}

void PBRMaterial::use()
{
    if (true)
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

Material *PBRMaterial::loadFromFile(const std::string &filename)
{
    PBRMaterial *material = new PBRMaterial();

    std::ifstream file(filename);
    if (!file.is_open())
    {
        Log::error(LogCategory::Application, "File not found: Material " + filename);
    }

    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string contents = fileStream.str();
    rapidjson::StringStream jsonStr(contents.c_str());
    rapidjson::Document doc;
    doc.ParseStream(jsonStr);

    if (!doc.IsObject())
    {
        std::ostringstream s;
        s << "Material " << filename << " is not valid json";
        Log::error(LogCategory::Application, s.str());
    }

    material->setShaderName(doc["shader"].GetString());
    material->setRoughness(static_cast<float>(doc["roughness"].GetDouble()));

    Log::info("Loaded phong material " + filename + " with shader " + doc["shader"].GetString());

    return material;
}
