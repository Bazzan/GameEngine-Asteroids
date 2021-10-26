#include "TextureManager.h"
#include "GameInstance.h"


/// <summary>
/// Creates a texture using SDLs built in functions
/// </summary>
/// <param name="texture"></param>
/// <returns></returns>
SDL_Texture *TextureManager::LoadTexture(const char *texture)
{
	SDL_Surface *tempSurface = IMG_Load(texture);
	SDL_Texture *tex = SDL_CreateTextureFromSurface(GameInstance::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

/// <summary>
/// Draws a texture without turning it
/// </summary>
/// <param name="tex"></param>
/// <param name="src"></param>
/// <param name="dest"></param>
/// <param name="flip"></param>
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(GameInstance::renderer, tex, &src, &dest, NULL, NULL, flip);
}
/// <summary>
/// draws a texture with the possibility of turning it
/// </summary>
/// <param name="tex"></param>
/// <param name="src"></param>
/// <param name="dest"></param>
/// <param name="angle"></param>
/// <param name="flip"></param>
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, float angle, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(GameInstance::renderer, tex, &src, &dest, angle, NULL, flip);
}