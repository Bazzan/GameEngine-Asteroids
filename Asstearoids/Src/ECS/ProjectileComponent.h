#pragma once

#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"


/// <summary>
/// Componenta added to projectiles.
/// Handles the velocity and destruction 
/// </summary>
class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel)
	{

	}
	~ProjectileComponent()
	{

	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}
	/// <summary>
	/// destroys the object when it has travelled a set distance
	/// </summary>
	void update() override
	{
		distance += speed;

		if(distance > range)
		{
			std::cout << "Out of range" << std::endl;
			entity->destroy();
		}
		
	}

private:
	TransformComponent *transform;
	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;


};