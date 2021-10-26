#pragma once
#include <string>
#include <SDL.h>
#include "Components.h"
#include "../TextureManager.h"


/// <summary>
/// Class for setting up and updating collider
/// </summary>
class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture *tex;
	SDL_Rect srcR, destR;

	TransformComponent *transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	/// <summary>
	/// makes sure that everything that has a collider also has a transform
	/// </summary>
	void init() override
	{
		if(!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		destR = { collider.x, collider.y, collider.w, collider.h };

	}
	/// <summary>
	/// updates the position of the collider to the transforms postition
	/// except for the background
	/// </summary>
	void update() override
	{

		if(tag != "terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);

			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

		destR.x = collider.x;
		destR.y = collider.y;

	}
};