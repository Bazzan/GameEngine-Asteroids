#include "Collision.h"
#include "ECS/ColliderComponent.h"
/// <summary>
/// AABB standard collision
/// Checks if boxes are inside of eachother using 
/// sdl rects
/// </summary>
/// <param name="recA"></param>
/// <param name="recB"></param>
/// <returns></returns>
bool Collision::AABB(const SDL_Rect &recA, const SDL_Rect &recB)
{
	if(recA.x + recA.w >= recB.x &&
	   recB.x + recB.w >= recA.x &&
	   recA.y + recA.h >= recB.y &&
	   recB.y + recB.h >= recA.y)
	{
		return true;
	}
	return false;
}

/// <summary>
/// AABB standard collision
/// Checks if boxes are inside of eachother using 
/// collider component
/// </summary>
/// <param name="colA"></param>
/// <param name="colB"></param>
/// <returns></returns>
bool Collision::AABB(const ColliderComponent &colA, const ColliderComponent &colB)
{
	if(AABB(colA.collider, colB.collider))
	{
		std::cout << colA.tag << "hit: " << colB.tag << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

