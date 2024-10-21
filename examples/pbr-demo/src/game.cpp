#include <chani.h>

#include "pbrMaterial.h"
#include <actor.h>
#include <assets.h>
#include <maths.h>
#include <orbitActor.h>
#include <phongMaterial.h>
#include <sphere.h>

#define ROWS 2
#define COLUMNS 10
#define SPACING 1000

OrbitActor *orbit;
Sphere *spheres[ROWS][COLUMNS];

int x, y = 0;

void Game::load()
{
    inputSystem.setMouseRelativeMode(window.getSDLWindow(), false);

    Assets::loadShader("assets/shaders/Phong.vert", "assets/shaders/Phong.frag", "", "", "", "Shader_Phong");
    Assets::loadShader("assets/shaders/PBR.vert", "assets/shaders/PBR.frag", "", "", "", "Shader_PBR");

    Assets::loadTexture(renderer, "assets/textures/Sphere.png", "Texture_Sphere");

    Assets::loadMesh("assets/meshes/Sphere.gpmesh", "Mesh_Sphere");

    Assets::loadPhongMaterial("assets/materials/Phong.mat", "Material_Phong");
    Assets::loadCustomMaterial(PBRMaterial::loadFromFile("assets/materials/PBR.mat"), "Material_PBR");

    float step = 100.0f / COLUMNS;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            spheres[i][j] = new Sphere();
            spheres[i][j]->setPosition(Vector3(0.0f, (float)(j * SPACING), -(float)(i * SPACING)));
            spheres[i][j]->setScale(10.0f);

            if (i == 0)
            {
                /*PhongMaterial *mat = dynamic_cast<PhongMaterial
                 * *>(Assets::getMaterial("Material_Phong")->makeUnique());*/
                /*mat->setSpecular((float)j * step);*/
                spheres[i][j]->getMeshComponent()->setMaterial(Assets::getMaterial("Material_Phong"));
            }
            if (i == 1)
            {
                /*PBRMaterial *mat = dynamic_cast<PBRMaterial
                 * *>(Assets::getMaterial("Material_PBR")->makeUnique());*/
                /*mat->setRoughness((float)j * step);*/
                spheres[i][j]->getMeshComponent()->setMaterial(Assets::getMaterial("Material_PBR"));
            }
        }
    }

    orbit = new OrbitActor();
    orbit->snapToActor(spheres[y][x]);

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

    // Escape: quit game
    if (input.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
    {
        isRunning = false;
    }

    if (input.keyboard.getKeyState(SDL_SCANCODE_UP) == ButtonState::Pressed)
    {
        y++;
    }
    if (input.keyboard.getKeyState(SDL_SCANCODE_DOWN) == ButtonState::Pressed)
    {
        y--;
    }
    if (input.keyboard.getKeyState(SDL_SCANCODE_RIGHT) == ButtonState::Pressed)
    {
        x++;
    }
    if (input.keyboard.getKeyState(SDL_SCANCODE_LEFT) == ButtonState::Pressed)
    {
        x--;
    }

    y = Maths::wrap(y, 0, ROWS);
    x = Maths::wrap(x, 0, COLUMNS);

    orbit->snapToActor(spheres[y][x]);

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
