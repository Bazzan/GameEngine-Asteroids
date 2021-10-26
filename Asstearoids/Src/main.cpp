#include "GameInstance.h"

GameInstance *gameInstance = nullptr;

/// <summary>
/// Gameloop and initiliser for the game
/// capped framerate at 60
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char *argv[])
{

	const int fps = 60; //target fps
	const int frameDelay = 1000 / fps; //max time between frames

	Uint32 frameStart;
	int frameTime;

	gameInstance = new GameInstance();
	gameInstance->init("GameWindow", 800, 640, false); //divisible by 32

	while (gameInstance->running())
	{
		
		frameStart = SDL_GetTicks();


		gameInstance->handleEvents();
		gameInstance->update();
		gameInstance->render();

		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
		{
			float deltaTime = frameDelay - frameTime;
			gameInstance->Time += deltaTime/1000;
			SDL_Delay(deltaTime);
			
		}
	}

	gameInstance->Clean();
	return 0;
}