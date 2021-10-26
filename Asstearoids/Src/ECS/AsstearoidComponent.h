#pragma once
#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"

/// <summary>
/// Asstearoids sets a starting velocity for the transform
/// </summary>
class AsstearoidComponent : public Component
{
public:
	AsstearoidComponent() = default;
	AsstearoidComponent(Vector2D vel) : velocity(vel)
	{
	}
	~AsstearoidComponent()
	{
	}

	void init()override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

private:
	TransformComponent *transform;
	Vector2D velocity;
};
