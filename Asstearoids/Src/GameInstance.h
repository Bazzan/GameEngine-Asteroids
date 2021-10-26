#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class AssetManager;
class ColliderComponent;
class AssManager;

class GameInstance
{
public:

	GameInstance();
	~GameInstance();

	void init(const char* title, int width, int height, bool fullscreen);

	void LoadTextures();

	void CreatePlayer();


	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void DrawGame();
	void Clean();

	void Restart();

	static float Time;
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static bool isPaused;
	static AssetManager* assets;

	enum groupLables : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupAsstearoids
	};

private:

	int cnt = 0;
	SDL_Window* window;
};