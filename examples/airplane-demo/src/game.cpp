#include <chani.h>

#include "SDL_scancode.h"
#include "cloudMaterial.h"
#include <actor.h>
#include <assets.h>
#include <cloudComponent.h>
#include <inputSystem.h>
#include <log.h>
#include <maths.h>
#include <mouseState.h>
#include <orbitActor.h>
#include <phongMaterial.h>
#include <sphere.h>
#include <string>
#include <window.h>

// Sphere *sphere, *sphere2;
OrbitActor *orbit;
Actor *center;
CloudComponent *cloudComponent;

int x, y = 0;

float cloudScale = 0.2;
float persistence = 0.2f;
float cloudStrength = 50.0;

void Game::load()
{
    renderer.setClearColor(Vector3(0.6f, 0.8f, 1.0f));
    inputSystem.setMouseRelativeMode(window.getSDLWindow(), false);

    Assets::loadShader("assets/shaders/Cloud.vert", "assets/shaders/Cloud.frag", "", "", "", "Shader_Cloud");
    Assets::loadShader("assets/shaders/Phong.vert", "assets/shaders/Phong.frag", "", "", "", "Shader_Phong");

    Assets::loadTexture(renderer, "assets/textures/Sphere.png", "Texture_Sphere");

    Assets::loadMesh("assets/meshes/Sphere.gpmesh", "Mesh_Sphere");

    Assets::loadComputeShader("assets/shaders/PerlinNoise.glsl", "CS_PerlinNoise");

    Assets::loadCustomMaterial(CloudMaterial::loadFromFile("assets/materials/Cloud.mat"), "Material_Cloud");
    Assets::loadPhongMaterial("assets/materials/Phong.mat", "Material_Phong");

    static_cast<CloudMaterial *>(Assets::getMaterial("Material_Cloud"))->setScale(&cloudScale);
    static_cast<CloudMaterial *>(Assets::getMaterial("Material_Cloud"))->setStrength(&cloudStrength);
    static_cast<CloudMaterial *>(Assets::getMaterial("Material_Cloud"))->setPersistence(&persistence);

    // sphere = new Sphere();
    // sphere->setPosition(Vector3(0.0f, 0.0f, 0.0f));
    // sphere->setScale(10.0f);

    // sphere2 = new Sphere();
    // sphere2->setPosition(Vector3(200.0f, 200.0f, 0.0f));
    // sphere2->setScale(10.0f);

    center = new Actor();
    center->setPosition(Vector3(0.0f, 0.0f, 0.0f));

    orbit = new OrbitActor();
    orbit->snapToActor(center);

    Cuboid *area = new Cuboid({Vector3<float>(-2000.0f, -2000.0f, -100.0f), Vector3<float>(4000.0f, 4000.0f, 200.0f)});
    cloudComponent = new CloudComponent(orbit, area);

    orbit->addComponent(cloudComponent);

    // Setup lights
    renderer.setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
    DirectionalLight &dir = renderer.getDirectionalLight();
    dir.direction = Vector3(0.0f, -0.707f, -0.707f);
    dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
    dir.specColor = Vector3(0.8f, 0.8f, 0.8f);
}

void Game::processInput()
{
    inputSystem.preUpdate();

    // SDL Event
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        isRunning = inputSystem.processEvent(event);
    }

    inputSystem.update();
    const InputState &input = inputSystem.getInputState();

    if (input.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
    {
        isRunning = false;
    }

    if (input.keyboard.getKeyState(SDL_SCANCODE_R) == ButtonState::Released)
    {
        cloudComponent->reloadNoiseShader();
    }

    if (input.keyboard.getKeyState(SDL_SCANCODE_UP) == ButtonState::Released)
    {
        cloudStrength -= (cloudStrength > 1) ? 1 : 0;
        Log::info(std::to_string(cloudStrength));
    }

    if (input.keyboard.getKeyState(SDL_SCANCODE_DOWN) == ButtonState::Released)
    {
        cloudStrength += 1;
        Log::info(std::to_string(cloudStrength));
    }

    if (input.keyboard.getKeyState(SDL_SCANCODE_LSHIFT) == ButtonState::Held)
    {
        float pre = persistence;
        persistence += (float)input.mouse.getScrollWheel().y * 0.01f;
        persistence = (persistence > 1.0f) ? persistence = 1.0f : persistence;
        persistence = (persistence < -1.0f) ? persistence = -1.0f : persistence;
        if (pre != persistence)
            Log::info(std::to_string(persistence));
    }
    if (input.keyboard.getKeyState(SDL_SCANCODE_LCTRL) == ButtonState::Held)
    {
        float pre = cloudScale;
        cloudScale *= 1.0f + ((float)input.mouse.getScrollWheel().y * 0.1f);
        cloudScale = (cloudScale < 0.1f) ? cloudScale = 0.2f : cloudScale;
        if (pre != cloudScale)
            Log::info(std::to_string(cloudScale));
    }

    // Actor input
    isUpdatingActors = true;
    for (auto actor : actors)
    {
        actor->processInput(input);
    }
    isUpdatingActors = false;
}

void Game::update(float dt)
{
    // Update actors
    isUpdatingActors = true;
    for (auto actor : actors)
    {
        actor->update(dt);
    }
    isUpdatingActors = false;

    // Move pending actors to actors
    for (auto pendingActor : pendingActors)
    {
        pendingActor->computeWorldTransform();
        actors.emplace_back(pendingActor);
    }
    pendingActors.clear();

    // Delete dead actors
    std::vector<Actor *> deadActors;
    for (auto actor : actors)
    {
        if (actor->getState() == Actor::ActorState::Dead)
        {
            deadActors.emplace_back(actor);
        }
    }

    for (auto deadActor : deadActors)
    {
        delete deadActor;
    }
}
