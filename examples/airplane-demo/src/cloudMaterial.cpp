#include "cloudMaterial.h"

#include "perlinNoise.h"
#include <assets.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <log.h>
#include <random.h>
#include <rapidjson/document.h>
#include <shader.h>
#include <sstream>
#include <texture.h>
#include <time.h>
#include <window.h>

clock_t clock_start = clock();

CloudMaterial::CloudMaterial() : Material() {
    noise1.load(PerlinSettings({200u, Vector3(5u, 5u, 1u)}));
    noise1.generate();
    noise2.load(PerlinSettings({50u, Vector3(10u, 10u, 4u)}));
    noise2.generate();
    noise3.load(PerlinSettings({10u, Vector3(10u, 10u, 5u)}));
    noise3.generate();
}

void CloudMaterial::use() {
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    getShader().use();

    GLenum e = glGetError();

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_3D, noise1.getNoiseTexture());
    getShader().setSampler3D("uPerlinNoise1", 4);
    getShader().setInteger("uTexture1Width", noise1.getTextureDimensions().x);
    getShader().setInteger("uTexture1Height", noise1.getTextureDimensions().y);

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_3D, noise2.getNoiseTexture());
    getShader().setSampler3D("uPerlinNoise2", 5);
    getShader().setInteger("uTexture2Width", noise2.getTextureDimensions().x);
    getShader().setInteger("uTexture2Height", noise2.getTextureDimensions().y);

    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_3D, noise3.getNoiseTexture());
    getShader().setSampler3D("uPerlinNoise3", 6);
    getShader().setInteger("uTexture3Width", noise3.getTextureDimensions().x);
    getShader().setInteger("uTexture3Height", noise3.getTextureDimensions().y);

    getShader().setVector3f("uAreaCorner", area->corner);
    getShader().setVector3f("uAreaSize", area->size);
    getShader().setVector3f("uShift", *shift);
    getShader().setFloat("uTime",
                         float(clock_start - clock()) / CLOCKS_PER_SEC);
    getShader().setMatrix4f("uViewProj", view * projection);
    getShader().setSampler2D("uScreenTexture", 1);
    getShader().setSampler2D("uDepthTexture", 2);
    getShader().setFloat("uNearPlane", RendererOGL::nearPlane);
    getShader().setFloat("uFarPlane", RendererOGL::farPlane);
    getShader().setInteger("uScreenWidth", WINDOW_WIDTH);
    getShader().setInteger("uScreenHeight", WINDOW_HEIGHT);
}

void CloudMaterial::setArea(Cuboid *cuboid) { area = cuboid; }

void CloudMaterial::setShift(Vector3<float> *shiftP) { shift = shiftP; }

void CloudMaterial::reload() {
    noise1.reload();
    noise2.reload();
    noise3.reload();
}

Material *CloudMaterial::makeUnique() {
    CloudMaterial *newMat = new CloudMaterial();

    newMat->noise1 = noise1;
    newMat->noise2 = noise2;
    newMat->noise3 = noise3;
    newMat->view = view;
    newMat->projection = projection;
    newMat->spriteViewProj = spriteViewProj;
    newMat->shaderName = shaderName;
    newMat->area = area;

    Assets::loadCustomMaterial(newMat, Random::getUUID().c_str());

    return newMat;
}

Material *CloudMaterial::loadFromFile(const std::string &filename) {
    CloudMaterial *material = new CloudMaterial();

    std::ifstream file(filename);
    if (!file.is_open()) {
        Log::error(LogCategory::Application,
                   "File not found: Material " + filename);
    }

    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string contents = fileStream.str();
    rapidjson::StringStream jsonStr(contents.c_str());
    rapidjson::Document doc;
    doc.ParseStream(jsonStr);

    if (!doc.IsObject()) {
        std::ostringstream s;
        s << "Material " << filename << " is not valid json";
        Log::error(LogCategory::Application, s.str());
    }

    material->setShaderName(doc["shader"].GetString());

    Log::info("Loaded cloud material " + filename + " with shader " +
              doc["shader"].GetString());

    return material;
}
