#include <chani.h>

#include "cloudMaterial.h"
#include <actor.h>
#include <assets.h>
#include <cloudComponent.h>
#include <inputSystem.h>
#include <maths.h>
#include <orbitActor.h>
#include <phongMaterial.h>
#include <sphere.h>
#include <window.h>

Sphere *sphere, *sphere2;
OrbitActor *orbit;
CloudComponent *cloudComponent;

int x, y = 0;

void Game::load()
{
    renderer.setClearColor(Vector3(0.6f, 0.8f, 1.0f));
    inputSystem.setMouseRelativeMode(window.getSDLWindow(), false);

    Assets::loadShader("assets/shaders/Cloud.vert", "assets/shaders/Cloud.frag", "", "", "", "Shader_Cloud");
    Assets::loadShader("assets/shaders/Phong.vert", "assets/shaders/Phong.frag", "", "", "", "Shader_Phong");

    Assets::loadTexture(renderer, "assets/textures/Sphere.png", "Texture_Sphere");

    Assets::loadMesh("assets/meshes/Sphere.gpmesh", "Mesh_Sphere");

    PerlinSettings perlinSettings = {Vector3(9, 9, 1), Vector3(WINDOW_WIDTH, WINDOW_HEIGHT, 1)};

    Assets::loadComputeShader("assets/shaders/PerlinNoise.glsl", "CS_PerlinNoise");

    Assets::loadCustomMaterial(CloudMaterial::loadFromFile("assets/materials/Cloud.mat", perlinSettings),
                               "Material_Cloud");
    Assets::loadPhongMaterial("assets/materials/Phong.mat", "Material_Phong");

    sphere = new Sphere();
    sphere->setPosition(Vector3(0.0f, 0.0f, 0.0f));
    sphere->setScale(10.0f);

    sphere2 = new Sphere();
    sphere2->setPosition(Vector3(200.0f, 200.0f, 0.0f));
    sphere2->setScale(10.0f);

    orbit = new OrbitActor();
    orbit->snapToActor(sphere);

    Cuboid *area = new Cuboid({Vector3(-200.0f, -200.0f, -50.0f), Vector3(400.0f, 400.0f, 100.0f)});
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
