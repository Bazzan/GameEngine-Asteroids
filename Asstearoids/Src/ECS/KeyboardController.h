#pragma once
#include "../GameInstance.h"
#include "ECS.h"
#include "Components.h"
#include "../AssetManager.h"


/// <summary>
/// Class for handling input of the player.
/// This component is only applied to the player so it is not possible for multiple inputs
/// </summary>
class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	int count;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}
	/// <summary>
	/// Input handling
	/// </summary>
	void update() override
	{

		transform->velocity.x *= .99f;
		transform->velocity.y *= .99f;

		SDL_PumpEvents();
		transform->SetCenter();
		transform->UpdateForward(transform->TAngle);

		state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_W]) {
			transform->velocity = transform->GetForward();
			isPressingW = true;
		}
		if (state[SDL_SCANCODE_A]) {
			transform->TAngle += 4;
			transform->UpdateForward(transform->TAngle);
			sprite->turnSpeed = transform->forwardToDegrees(transform->GetForward());
		}
		if (state[SDL_SCANCODE_D]) {
			transform->TAngle -= 4;
			transform->UpdateForward(transform->TAngle);
			sprite->turnSpeed = transform->forwardToDegrees(transform->GetForward());
		}
		if (state[SDL_SCANCODE_SPACE]) {
			if (GameInstance::Time < timeToNextShot) return;
			transform->SetCenter();
			GameInstance::assets->CreateProjectile(transform->GetCenter(), transform->NormalizeVector2D(
				(transform->GetForward() + transform->GetCenter()) - transform->GetCenter()) + transform->velocity,
				500, 5, "point");
			timeToNextShot = GameInstance::Time + ShootCD;
		}

		if (GameInstance::event.type == SDL_KEYDOWN)
		{
			switch (GameInstance::event.key.keysym.sym)
			{
			case SDLK_0:
				std::cout << transform->position << "pos" << std::endl;
				std::cout << transform->GetCenter() << " Center" << std::endl;
				break;
			case SDLK_ESCAPE:
				GameInstance::isRunning = false;
				break;
			default:
				break;
			}
		}
	}

private:
	const Uint8* state;
	const float ShootCD = 0.5f;
	float timeToNextShot = 0;
	bool isPressingW = false;
};