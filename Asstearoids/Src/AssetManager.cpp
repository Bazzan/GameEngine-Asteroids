#include "AssetManager.h"
#include "ECS/Components.h"

AssetManager::AssetManager(EntityManager *man) : manager(man)
{

}

AssetManager::~AssetManager()
{

}

/// <summary>
/// Creates a projectile at desired position
/// and adds required components to it.
/// </summary>
/// <param name="pos"></param>
/// <param name="vel"></param>
/// <param name="range"></param>
/// <param name="speed"></param>
/// <param name="id"></param>
void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
	auto &projectile(manager->addentity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 5, 5, 1);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("Projectile");
	projectile.addGroup(GameInstance::groupProjectiles);
}

/// <summary>
/// Creates a asstearoid at desired position
/// and adds required components to it.
/// </summary>
/// <param name="pos"></param>
/// <param name="vel"></param>
/// <param name="speed"></param>
/// <param name="rot"></param>
/// <param name="sc"></param>
/// <param name="id"></param>
void AssetManager::CreateAsstearoid(Vector2D pos, Vector2D vel, int speed, float rot, int sc, std::string id)
{
	auto &asstearoid(manager->addentity());
	asstearoid.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, sc);
	asstearoid.addComponent<SpriteComponent>(id, false);
	asstearoid.addComponent<AsstearoidComponent>(vel);
	asstearoid.addComponent<ColliderComponent>("Asstearoid");
	asstearoid.addGroup(GameInstance::groupAsstearoids);
}

/// <summary>
/// Spawns asstearoid with random position and velocity
/// </summary>
void AssetManager::SpawnAss()
{
	Vector2D spawn = GetSpawnPoint();
	Vector2D vel = GetVel();

	CreateAsstearoid(spawn, vel, 1, 36, rand() % 2 + 1, "Ass");
}

void AssetManager::SetWindowSize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
}


/// <summary>
/// Creates a spawnpoint for asstearoids at a side of the window
/// </summary>
/// <returns></returns>
Vector2D AssetManager::GetSpawnPoint()
{
	int side = rand() % 4 + 1;
	int randHeight = rand() % windowHeight;
	int randWidth = rand() % windowWidth;
	if(side == 1)
	{
		return Vector2D(randWidth, 0.0 - 32);

	}
	else if(side == 2)
	{
		return Vector2D(randWidth, 640 + 32);
	}
	else if(side == 3)
	{
		return Vector2D(0.0 - 32, randHeight);
	}
	else if(side == 4)
	{
		return Vector2D(800 + 32, randHeight);
	}

}

/// <summary>
/// random velocity between 0-1
/// </summary>
/// <returns></returns>
Vector2D AssetManager::GetVel()
{
	float randX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float randY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	return Vector2D(randX, randY);
}

/// <summary>
/// Adds a texture to texture manager
/// </summary>
/// <param name="id"></param>
/// <param name="path"></param>
void AssetManager::AddTexture(std::string id, const char *path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}
/// <summary>
/// Gets texture from texture manager
/// </summary>
/// <param name="id"></param>
/// <returns></returns>
SDL_Texture *AssetManager::GetTexture(std::string id)
{
	return textures[id];
}