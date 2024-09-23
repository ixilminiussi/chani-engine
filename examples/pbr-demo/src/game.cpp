#include <chani.h>

#include <actor.h>
#include <assets.h>
#include <orbitActor.h>
#include <sphere.h>

OrbitActor *orbit;
Sphere *spheres[3];

void Game::load() {
    inputSystem.setMouseRelativeMode(window.getSDLWindow(), false);

    Assets::loadShader("assets/shaders/Sprite.vert",
                       "assets/shaders/Sprite.frag", "", "", "", "Sprite");
    Assets::loadShader("assets/shaders/Phong.vert", "assets/shaders/Phong.frag",
                       "", "", "", "Phong");
    Assets::loadShader("assets/shaders/BasicMesh.vert",
                       "assets/shaders/BasicMesh.frag", "", "", "",
                       "BasicMesh");

    Assets::loadTexture(renderer, "assets/textures/Sphere.png", "Sphere");

    Assets::loadMesh("assets/meshes/Sphere.gpmesh", "Mesh_Sphere");

    spheres[0] = new Sphere();
    spheres[1] = new Sphere();
    spheres[2] = new Sphere();

    spheres[0]->setPosition(Vector3(-100.0f, 0.0f, 0.0f));
    spheres[0]->setScale(10.0f);

    spheres[1]->setPosition(Vector3(-100.0f, 0.0f, 0.0f));
    spheres[1]->setScale(10.0f);

    spheres[2]->setPosition(Vector3(-100.0f, 0.0f, 0.0f));
    spheres[2]->setScale(10.0f);

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
