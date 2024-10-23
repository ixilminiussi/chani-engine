#include "cloudMaterial.h"

#include <assets.h>
#include <fstream>
#include <iostream>
#include <log.h>
#include <random.h>
#include <rapidjson/document.h>
#include <shader.h>
#include <sstream>

CloudMaterial::CloudMaterial() : Material()
{
}

void CloudMaterial::use()
{
    getShader().use();

    getShader().setMatrix4("uViewProj", view * projection);
    getShader().setSampler2D("uScreenTexture", GL_TEXTURE0);
    getShader().setSampler2D("uDepthTexture", GL_TEXTURE1);

    glDisable(GL_DEPTH_TEST);
}

Material *CloudMaterial::makeUnique()
{
    CloudMaterial *newMat = new CloudMaterial();

    newMat->view = view;
    newMat->projection = projection;
    newMat->spriteViewProj = spriteViewProj;
    newMat->shaderName = shaderName;

    Assets::loadCustomMaterial(newMat, Random::getUUID().c_str());

    return newMat;
}

Material *CloudMaterial::loadFromFile(const std::string &filename)
{
    CloudMaterial *material = new CloudMaterial();

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

    Log::info("Loaded cloud material " + filename + " with shader " + doc["shader"].GetString());

    return material;
}
