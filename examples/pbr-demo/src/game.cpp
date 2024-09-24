#include <chani.h>

#include <actor.h>
#include <assets.h>
#include <orbitActor.h>
#include <sphere.h>

OrbitActor *orbit;
Sphere *spheres[3];

void Game::load() {
    inputSystem.setMouseRelativeMode(window.getSDLWindow(), false);

    Assets::loadShader("assets/shaders/Phong.vert", "assets/shaders/Phong.frag",
                       "", "", "", "Shader_Phong");

    Assets::loadTexture(renderer, "assets/textures/Sphere.png",
                        "Texture_Sphere");

    Assets::loadMesh("assets/meshes/Sphere.gpmesh", "Mesh_Sphere");

    Assets::loadPhongMaterial("assets/materials/Phong10.mat", "Material_Phong_10");
    Assets::loadPhongMaterial("assets/materials/Phong50.mat", "Material_Phong_50");
    Assets::loadPhongMaterial("assets/materials/Phong90.mat", "Material_Phong_90");

    spheres[0] = new Sphere();
    spheres[1] = new Sphere();
    spheres[2] = new Sphere();

    spheres[0]->setPosition(Vector3(-1000.0f, 0.0f, 0.0f));
    spheres[0]->setScale(10.0f);
    spheres[0]->getMeshComponent()->setMaterial(Assets::getMaterial("Material_Phong_10"));

    spheres[1]->setPosition(Vector3(0.0f, 0.0f, 0.0f));
    spheres[1]->setScale(10.0f);
    spheres[1]->getMeshComponent()->setMaterial(Assets::getMaterial("Material_Phong_50"));

    spheres[2]->setPosition(Vector3(1000.0f, 0.0f, 0.0f));
    spheres[2]->setScale(10.0f);
    spheres[2]->getMeshComponent()->setMaterial(Assets::getMaterial("Material_Phong_90"));

    orbit = new OrbitActor();
    orbit->snapToActor(spheres[0]);

    // Setup lights
    renderer.setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
    DirectionalLight &dir = renderer.getDirectionalLight();
    dir.direction = Vector3(0.0f, -0.707f, -0.707f);
    dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
    dir.specColor = Vector3(0.8f, 0.8f, 0.8f);
}

void Game::processInput() {
    inputSystem.preUpdate();

    // SDL Event
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        isRunning = inputSystem.processEvent(event);
    }

    inputSystem.update();
    const InputState &input = inputSystem.getInputState();

    // Escape: quit game
    if (input.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) ==
        ButtonState::Released) {
        isRunning = false;
    }

    if (input.keyboard.getKeyState(SDL_SCANCODE_1) == ButtonState::Pressed) {
        orbit->snapToActor(spheres[0]);
    }
    if (input.keyboard.getKeyState(SDL_SCANCODE_2) == ButtonState::Pressed) {
        orbit->snapToActor(spheres[1]);
    }
    if (input.keyboard.getKeyState(SDL_SCANCODE_3) == ButtonState::Pressed) {
        orbit->snapToActor(spheres[2]);
    }

    // Actor input
    isUpdatingActors = true;
    for (auto actor : actors) {
        actor->processInput(input);
    }
    isUpdatingActors = false;
}

void Game::update(float dt) {
    // Update actors
    isUpdatingActors = true;
    for (auto actor : actors) {
        actor->update(dt);
    }
    isUpdatingActors = false;

    // Move pending actors to actors
    for (auto pendingActor : pendingActors) {
        pendingActor->computeWorldTransform();
        actors.emplace_back(pendingActor);
    }
    pendingActors.clear();

    // Delete dead actors
    std::vector<Actor *> deadActors;
    for (auto actor : actors) {
        if (actor->getState() == Actor::ActorState::Dead) {
            deadActors.emplace_back(actor);
        }
    }

    for (auto deadActor : deadActors) {
        delete deadActor;
    }
}
