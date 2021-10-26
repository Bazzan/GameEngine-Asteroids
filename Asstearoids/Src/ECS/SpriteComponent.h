#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>
#include "../AssetManager.h"


/// <summary>
/// Handles the drawing of sprites.
/// </summary>
class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;
	
	// start: for animation
	bool animated = false;
	int frames = 0;
	int speed = 100; //delay between frames in ms
	// end: for animation



public:
	float turnSpeed = 0;
	int animIndex = 0;
	std::map<const char *, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		setTex(id);
	}

	//for animated
	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);


		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");
		setTex(id);
	}


	~SpriteComponent()
	{
		
	}
	/// <summary>
	/// Fetches the Id of the sprite from the asset manager
	/// </summary>
	/// <param name="id"></param>
	void setTex(std::string id)
	{
		texture = GameInstance::assets->GetTexture(id);
	}
	/// <summary>
	/// Sets the sprite to match the transform
	/// </summary>
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}
	/// <summary>
	/// updates the sprite to match the transform
	/// </summary>
	void update() override
	{
		if(animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, turnSpeed , spriteFlip);
	}

	void Play(const char *animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
	
};