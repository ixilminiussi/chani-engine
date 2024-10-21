#include "game.h"
#include "racingCarActor.h"

#include <actor.h>
#include <assets.h>
#include <audioComponent.h>
#include <chani.h>
#include <cube.h>
#include <meshComponent.h>
#include <plane.h>
#include <sphere.h>
#include <timer.h>

void Game::load() {
    inputSystem.setMouseRelativeMode(window.getSDLWindow(), true);

    Assets::loadShader("assets/shaders/Sprite.vert",
                       "assets/shaders/Sprite.frag", "", "", "", "Sprite");
    Assets::loadShader("assets/shaders/Phong.vert", "assets/shaders/Phong.frag",
                       "", "", "", "Phong");
    Assets::loadShader("assets/shaders/BasicMesh.vert",
                       "assets/shaders/BasicMesh.frag", "", "", "",
                       "BasicMesh");

    Assets::loadTexture(renderer, "assets/textures/Default.png", "Default");
    Assets::loadTexture(renderer, "assets/textures/Cube.png", "Cube");
    Assets::loadTexture(renderer, "assets/textures/HealthBar.png", "HealthBar");
    Assets::loadTexture(renderer, "assets/textures/Plane.png", "Plane");
    Assets::loadTexture(renderer, "assets/textures/Radar.png", "Radar");
    Assets::loadTexture(renderer, "assets/textures/Sphere.png", "Sphere");
    Assets::loadTexture(renderer, "assets/textures/Crosshair.png", "Crosshair");
    Assets::loadTexture(renderer, "assets/textures/RacingCar.png", "RacingCar");
    Assets::loadTexture(renderer, "assets/textures/Rifle.png", "Rifle");

    Assets::loadPhongMaterial("assets/materials/CatWarrior.mat",
                              "Mat_CatWarrior");
    Assets::loadPhongMaterial("assets/materials/Cube.mat", "Mat_Cube");
    Assets::loadPhongMaterial("assets/materials/Plane.mat", "Mat_Plane");
    Assets::loadPhongMaterial("assets/materials/RacingCar.mat",
                              "Mat_RacingCar");
    Assets::loadPhongMaterial("assets/materials/Rifle.mat", "Mat_Rifle");
    Assets::loadPhongMaterial("assets/materials/Sphere.mat", "Mat_Sphere");
    Assets::loadPhongMaterial("assets/materials/Target.mat", "Mat_Target");
    Assets::loadSpriteMaterial("assets/materials/Crosshair.mat",
                               "Mat_Crosshair");

    Assets::loadMesh("assets/meshes/Cube.gpmesh", "Mesh_Cube");
    Assets::loadMesh("assets/meshes/Plane.gpmesh", "Mesh_Plane");
    Assets::loadMesh("assets/meshes/Sphere.gpmesh", "Mesh_Sphere");
    Assets::loadMesh("assets/meshes/Rifle.gpmesh", "Mesh_Rifle");
    Assets::loadMesh("assets/meshes/RacingCar.gpmesh", "Mesh_RacingCar");

    renderer.setClearColor(
        Vector3(128.0f / 255.f, 218.0f / 255.0f, 235.0f / 255.0f));

    fps = new FPSActor();
    racingCar = new RacingCarActor();
    orbit = new OrbitActor();
    path = new SplineActor();

    Cube *a = new Cube();
    a->setPosition(Vector3(200.0f, 105.0f, 0.0f));
    a->setScale(100.0f);
    Quaternion q(Vector3::unitY, -Maths::piOver2);
    q = Quaternion::concatenate(
        q, Quaternion(Vector3::unitZ, Maths::pi + Maths::pi / 4.0f));
    a->setRotation(q);

    Sphere *b = new Sphere();
    b->setPosition(Vector3(200.0f, -75.0f, 0.0f));
    b->setScale(3.0f);

    // Floor and walls

    // Setup floor
    const float start = -1250.0f;
    const float size = 250.0f;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            Plane *p = new Plane();
            p->setPosition(
                Vector3(start + i * size, start + j * size, -100.0f));
        }
    }

    // Left/right walls
    q = Quaternion(Vector3::unitX, Maths::piOver2);
    for (int i = 0; i < 10; i++) {
        Plane *p = new Plane();
        p->setPosition(Vector3(start + i * size, start - size, 0.0f));
        p->setRotation(q);

        p = new Plane();
        p->setPosition(Vector3(start + i * size, -start + size, 0.0f));
        p->setRotation(q);
    }

    q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::piOver2));
    // Forward/back walls
    for (int i = 0; i < 10; i++) {
        Plane *p = new Plane();
        p->setPosition(Vector3(start - size, start + i * size, 0.0f));
        p->setRotation(q);

        p = new Plane();
        p->setPosition(Vector3(-start + size, start + i * size, 0.0f));
        p->setRotation(q);
    }

    // Setup lights
    renderer.setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
    DirectionalLight &dir = renderer.getDirectionalLight();
    dir.direction = Vector3(0.0f, -0.707f, -0.707f);
    dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
    dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

    // Create spheres with audio components playing different sounds
    Sphere *soundSphere = new Sphere();
    soundSphere->setPosition(Vector3(500.0f, -75.0f, 0.0f));
    soundSphere->setScale(1.0f);
    AudioComponent *ac = new AudioComponent(soundSphere);
    ac->playEvent("event:/FireLoop");

    // Corsshair
    Actor *crosshairActor = new Actor();
    crosshairActor->setScale(2.0f);
    crosshair =
        new SpriteComponent(crosshairActor, Assets::getTexture("Crosshair"));
    crosshair->setMaterial(Assets::getMaterial("Mat_Crosshair"));

    // Start music
    musicEvent = audioSystem.playEvent("event:/Music");

    changeCamera(1);
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
        changeCamera(1);
    } else if (input.keyboard.getKeyState(SDL_SCANCODE_2) ==
               ButtonState::Pressed) {
        changeCamera(2);
    } else if (input.keyboard.getKeyState(SDL_SCANCODE_3) ==
               ButtonState::Pressed) {
        changeCamera(3);
    } else if (input.keyboard.getKeyState(SDL_SCANCODE_4) ==
               ButtonState::Pressed) {
        changeCamera(4);
    }

    // Actor input
    isUpdatingActors = true;
    for (auto actor : actors) {
        actor->processInput(input);
    }
    isUpdatingActors = false;
}

void Game::update(float dt) {
    // Update audio
    audioSystem.update(dt);

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

void changeCamera(int mode) {
    // Disable everything
    fps->setState(Actor::ActorState::Paused);
    fps->setVisible(false);
    crosshair->setVisible(false);
    racingCar->setState(Actor::ActorState::Paused);
    racingCar->setVisible(false);
    orbit->setState(Actor::ActorState::Paused);
    orbit->setVisible(false);
    path->setState(Actor::ActorState::Paused);

    // Enable the camera specified by the mode
    switch (mode) {
    case 1:
    default:
        fps->setState(Actor::ActorState::Active);
        fps->setVisible(true);
        crosshair->setVisible(true);
        break;
    case 2:
        racingCar->setState(Actor::ActorState::Active);
        racingCar->setVisible(true);
        break;
    case 3:
        orbit->setState(Actor::ActorState::Active);
        orbit->setVisible(true);
        break;
    case 4:
        path->setState(Actor::ActorState::Active);
        path->restartSpline();
        break;
    }
}
