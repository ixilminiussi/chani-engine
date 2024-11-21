#include "cloudComponent.h"

#include "cloudMaterial.h"
#include "imgui.h"
#include <assets.h>
#include <chani.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <log.h>
#include <mesh.h>
#include <postProcessComponent.h>
#include <shader.h>

CloudComponent::CloudComponent(Actor *ownerP, Cuboid *cuboid) : PostProcessComponent(ownerP), area(cuboid)
{
    cloudMaterial = dynamic_cast<CloudMaterial *>(Assets::getMaterial("Material_Cloud"));
    cloudMaterial->setArea(cuboid);

    setMaterial(cloudMaterial);

    cloudMaterial->setScale(&cloudScale);
    cloudMaterial->setSquish(&cloudSquish);
    cloudMaterial->setFloor(&cloudFloor);
    cloudMaterial->setStrength(&cloudStrength);
    cloudMaterial->setTimeScale(&timeScale);
    cloudMaterial->setTransmittance(&cloudTransmittanceScale);
    cloudMaterial->setDarknessThreshold(&cloudDarknessThreshold);
    cloudMaterial->setLightAbsorption(&cloudLightAbsorption);
    cloudMaterial->setColor(cloudColor);

    cloudMaterial->addNoise({Vector3(6, 6, 4), 100, 2.0f, 1.0});
    cloudMaterial->addNoise({Vector3(10, 10, 8), 40, 1.2f, 0.9});
    cloudMaterial->addNoise({Vector3(30, 30, 20), 10, 0.2f, 1.2});
    cloudMaterial->addNoise({Vector3(50, 50, 20), 5, 0.1f, 1.5});
}

void CloudComponent::update(float dt)
{
    makeUI();
}

void CloudComponent::makeUI()
{
    // TODO: IMGUI for tooling
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Cloud Settings");

    ImGui::Text("Time");
    ImGui::SliderInt("Speed", &timeScale, 0, 100);
    ImGui::Text("Cloud Shape");
    ImGui::SliderFloat("floor", &cloudFloor, 0.0f, 1.0f);
    ImGui::SliderFloat("strength", &cloudStrength, 0.0f, 1.0f);
    ImGui::SliderFloat("transmittance", &cloudTransmittanceScale, 0.0f, 2.0f);
    ImGui::SliderFloat("darkness threshold", &cloudDarknessThreshold, 0.0f, 1.0f);
    ImGui::SliderFloat("light absorption", &cloudLightAbsorption, 0.0f, 3.0f);
    ImGui::ColorEdit3("color", cloudColor);

    float *squish[3] = {&cloudSquish.x, &cloudSquish.y, &cloudSquish.z};
    ImGui::SliderFloat3("squish", *squish, 0.01f, 1.0f);
    ImGui::SliderFloat("scale", &cloudScale, 0.1f, 10.0f);
    float *sizes[3] = {&area->size.x, &area->size.y, &area->size.z};
    ImGui::SliderFloat3("coverage", *sizes, 10.0f, 2000.0f);

    ImGui::End();

    cloudMaterial->makeUI();

    ImGui::EndFrame();
}
