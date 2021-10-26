#pragma once

#include "SDL_image.h"


class TextureManager
{
public:
	static SDL_Texture *LoadTexture(const char *fileName);
	static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
	static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, float angle, SDL_RendererFlip flip);

};