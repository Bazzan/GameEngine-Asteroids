#include "GameInstance.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"

/// <summary>
/// Global variables
/// </summary>
Map* map;
EntityManager manager;
SDL_Renderer* GameInstance::renderer = nullptr;
SDL_Event GameInstance::event;

AssetManager* GameInstance::assets = new AssetManager(&manager);
bool GameInstance::isRunning = false;
bool GameInstance::isPaused = false;
float GameInstance::Time = 0.0f;
auto& player(manager.addentity());

GameInstance::GameInstance()
{
}

GameInstance::~GameInstance()
{
}
/// <summary>
/// Initializes the gamewindow, renderer and the starting gameobjects
/// </summary>
/// <param name="title"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="fullscreen"></param>
void GameInstance::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	assets->SetWindowSize(width, height);


	LoadTextures();

	map = new Map("terrain", 1, 32);
	map->LoadMap("Assets/map.map", 25, 20);

	CreatePlayer();

	//Spawning starting assteroids
	for (int i = 0; i < 5; i++)
	{
		assets->SpawnAss();
	}
}



//Groups the different types together for easy access
auto& tiles(manager.getGroup(GameInstance::groupMap));
auto& players(manager.getGroup(GameInstance::groupPlayers));
auto& colliders(manager.getGroup(GameInstance::groupColliders));
auto& projectiles(manager.getGroup(GameInstance::groupProjectiles));
auto& asstearoids(manager.getGroup(GameInstance::groupAsstearoids));

void GameInstance::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}


/// <summary>
/// manager refreshes and updates all the enteties that exist.
/// And the groups are checked for collision
/// </summary>
void GameInstance::update()
{
	manager.refresh();
	manager.update();


	for (auto& a : asstearoids) //player vs asstearoid col
	{
		SDL_Rect aCollider = a->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, aCollider))
		{
			Restart();
			break;
		}
	}
	//projectile vs asteroid col
	for (auto& p : projectiles)
	{
		SDL_Rect pCollider = p->getComponent<ColliderComponent>().collider;
		for (auto& a : asstearoids)
		{
			if (Collision::AABB(pCollider, a->getComponent<ColliderComponent>().collider))
			{
				p->destroy();
				a->destroy();
				assets->SpawnAss();
			}
		}
	}
}


/// <summary>
/// The higher the render object is in this function the further back it renders
/// </summary>
void GameInstance::render()
{
	SDL_RenderClear(renderer);
	DrawGame();
	SDL_RenderPresent(renderer);
}

/// <summary>
/// Draws the game
/// </summary>
void GameInstance::DrawGame()
{
	for (auto& t : tiles) t->draw();
	for (auto& p : projectiles) p->draw();
	for (auto& p : players) p->draw();
	for (auto& a : asstearoids) a->draw();
}

/// <summary>
/// SDL build in cleanining for closing the game and destroying the SDL components
/// </summary>
void GameInstance::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


/// <summary>
/// Clears the screen and resets it to its starting state
/// </summary>
void GameInstance::Restart()
{
	for (auto& ass : asstearoids)
		ass->destroy();
	for (auto& p : projectiles)
		p->destroy();

	//Call menu here is you want to

	player.getComponent<TransformComponent>().position.x = 400;
	player.getComponent<TransformComponent>().position.y = 320;

	for (int i = 0; i < 5; i++)
	{
		assets->SpawnAss();
	}
}

void GameInstance::LoadTextures()
{
	//Loads all the textures to the texture manager
	assets->AddTexture("terrain", "Assets/terrain_ss.png");
	assets->AddTexture("ship", "Assets/Shit.png");
	assets->AddTexture("point", "Assets/Point.png");
	assets->AddTexture("Ass", "Assets/Asstearoid2.png");
}

void GameInstance::CreatePlayer()
{
	//Creating the player
	player.addComponent<TransformComponent>(400, 320, 32, 32, 1);
	player.addComponent<SpriteComponent>("ship");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
}