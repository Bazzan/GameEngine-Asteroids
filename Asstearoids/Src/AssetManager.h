#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"

/// <summary>
/// Class for managing assets. 
/// Such as spawning and adding textures
/// </summary>
class AssetManager
{
public:
	AssetManager(EntityManager *man);
	~AssetManager();

	//gameobjects
	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);
	void CreateAsstearoid(Vector2D pos, Vector2D vel, int speed, float rot, int sc, std::string id);
	
	//textures
	void AddTexture(std::string id, const char *path);
	SDL_Texture *GetTexture(std::string id);
	void SpawnAss();
	void SetWindowSize(int width, int height);
	Vector2D GetSpawnPoint();
	Vector2D GetVel();



private:

	EntityManager *manager;
	std::map<std::string, SDL_Texture *> textures;
	int activeAss = 1;
	int windowWidth;
	int windowHeight;
};
