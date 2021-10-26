#pragma once

#include "ECS.h"
#include "SDL.h"
#include "../AssetManager.h"

/// <summary>
/// Background tiles
/// </summary>
class TileComponent : public Component
{
public:

	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id)
	{

		texture = GameInstance::assets->GetTexture(id);

		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tsize * tscale;

	}

	void update() override
	{
		destRect.x = position.x;
		destRect.y = position.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};

