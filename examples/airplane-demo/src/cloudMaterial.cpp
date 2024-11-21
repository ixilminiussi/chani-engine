#include "cloudMaterial.h"

#include "imgui.h"
#include "perlinNoise.h"
#include <actor.h>
#include <assets.h>
#include <chani.h>
#include <computeShader.h>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <log.h>
#include <random.h>
#include <rapidjson/document.h>
#include <shader.h>
#include <sstream>
#include <texture.h>
#include <window.h>

CloudMaterial::CloudMaterial() : Material()
{
}

void CloudMaterial::use()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    getShader().use();

    GLenum e = glGetError();

    PerlinSettings perlinSettings[noiseCount];
    PaddedVector3 dimensions[noiseCount];

    for (int i = 0; i < noiseCount; i++)
    {
        perlinSettings[i] = noise[i].getSettings();
        dimensions[i].x = noise[i].getTextureDimensions().x;
        dimensions[i].y = noise[i].getTextureDimensions().y;
        dimensions[i].z = noise[i].getTextureDimensions().z;

        glActiveTexture(GL_TEXTURE3 + i);
        glBindTexture(GL_TEXTURE_3D, noise[i].getNoiseTexture());
    }

    GLuint settingsUbo;
    glGenBuffers(1, &settingsUbo);
    glBindBuffer(GL_UNIFORM_BUFFER, settingsUbo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(PerlinSettings) * noiseCount, perlinSettings, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, settingsUbo);

    GLuint dimensionsUbo;
    glGenBuffers(1, &dimensionsUbo);
    glBindBuffer(GL_UNIFORM_BUFFER, dimensionsUbo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(PaddedVector3) * noiseCount, dimensions, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, dimensionsUbo);

    getShader().setInteger("uNoiseCount", int(noiseCount));

    getShader().setVector3f("uAreaCorner", area->center - area->size / 2.0f);
    getShader().setVector3f("uAreaSize", area->size);
    getShader().setVector3f("uScale", *scale * *squish);
    getShader().setFloat("uFloor", *floor);
    getShader().setFloat("uStrength", *strength);
    getShader().setFloat("uTransmittanceScale", *transmittance);
    getShader().setFloat("uLightAbsorption", *lightAbsorption);
    getShader().setFloat("uDarknessThreshold", *darknessThreshold);
    getShader().setVector3f("uCloudColor", cloudColor[0], cloudColor[1], cloudColor[2]);
    Game &gameInstance = Game::instance();
    getShader().setFloat("uTime", *timeScale * gameInstance.time());
    getShader().setMatrix4f("uViewProj", view * projection);
    getShader().setMatrix4f("uView", view);
    getShader().setMatrix4f("uProj", projection);
    getShader().setSampler2D("uScreenTexture", 1);
    getShader().setSampler2D("uDepthTexture", 2);
    getShader().setFloat("uNearPlane", RendererOGL::nearPlane);
    getShader().setFloat("uFarPlane", RendererOGL::farPlane);
    getShader().setFloat("uFOV", RendererOGL::FOV);
    getShader().setInteger("uScreenWidth", WINDOW_WIDTH);
    getShader().setInteger("uScreenHeight", WINDOW_HEIGHT);
}

void CloudMaterial::setArea(Cuboid *cuboid)
{
    area = cuboid;
}

void CloudMaterial::setScale(float *scaleP)
{
    scale = scaleP;
}

void CloudMaterial::setSquish(Vector3<float> *squishP)
{
    squish = squishP;
}

void CloudMaterial::setFloor(float *floorP)
{
    floor = floorP;
}

void CloudMaterial::setStrength(float *strengthP)
{
    strength = strengthP;
}

void CloudMaterial::setDarknessThreshold(float *darknessThresholdP)
{
    darknessThreshold = darknessThresholdP;
}

void CloudMaterial::setLightAbsorption(float *lightAbsorptionP)
{
    lightAbsorption = lightAbsorptionP;
}

void CloudMaterial::setTimeScale(int *timeScaleP)
{
    timeScale = timeScaleP;
}

void CloudMaterial::setTransmittance(float *transmittanceP)
{
    transmittance = transmittanceP;
}

void CloudMaterial::setColor(float *cloudColorP)
{
    cloudColor = cloudColorP;
}

Material *CloudMaterial::makeUnique()
{
    CloudMaterial *newMat = new CloudMaterial();

    newMat->view = view;
    newMat->projection = projection;
    newMat->spriteViewProj = spriteViewProj;
    newMat->shaderName = shaderName;
    newMat->area = area;

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

void CloudMaterial::addNoise(const PerlinSettings &perlinSettings)
{
    if (noiseCount >= 10)
        return;

    noise[noiseCount] = PerlinNoise(perlinSettings);
    noise[noiseCount].generate();

    noiseCount++;
}

void CloudMaterial::makeUI()
{
    ImGui::Begin("Noise Settings");

    for (int i = 0; i < noiseCount; i++)
    {
        char buffer[50];
        ImGui::Text("Perlin Noise %d", i);
        std::sprintf(buffer, "Cell Scale %d", i);
        ImGui::SliderInt(buffer, &noise[i].getSettings().cellScale, 4, 500);

        int *sizes[3] = {&noise[i].getSettings().gridSize.x, &noise[i].getSettings().gridSize.y,
                         &noise[i].getSettings().gridSize.z};
        std::sprintf(buffer, "Grid Size %d", i);
        ImGui::SliderInt3(buffer, *sizes, 3, 100);
        std::sprintf(buffer, "Regenerate %d", i);
        if (ImGui::Button(buffer))
        {
            noise[i].generate();
        }
        std::sprintf(buffer, "Weight %d", i);
        ImGui::SliderFloat(buffer, &noise[i].getSettings().weight, 0.0f, 2.0f);
        std::sprintf(buffer, "Time Scale %d", i);
        ImGui::SliderFloat(buffer, &noise[i].getSettings().timeScale, 0.0f, 2.0f);
        ImGui::Spacing();
    }

    if (ImGui::Button("Add new"))
    {
        addNoise({Vector3(3, 3, 3), 5, 1.0f, 1.0f});
    }

    ImGui::End();
}
