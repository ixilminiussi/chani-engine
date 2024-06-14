#if !defined(GAME_H)
#define GAME_H

#include <vector>
#include "actor.h"
#include "spriteComponent.h"
#include "window.h"
#include "vector2.h"
#include "rendererOGL.h"
#include "camera.h"

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() : isRunning(true), isUpdatingActors(false), camera(nullptr) {}

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);
	RendererOGL& getRenderer() { return renderer; }

private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;
	Window window;
	RendererOGL renderer;

	bool isUpdatingActors;
    std::vector<Actor*> actors;
    std::vector<Actor*> pendingActors;
	Camera* camera;
};

#endif
