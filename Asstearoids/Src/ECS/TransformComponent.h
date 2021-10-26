#pragma once
#include "Components.h"
#include "../Vector2D.h"
#include <math.h>


/// <summary>
/// Transformcomponent keeps track of position and velocity.
/// also used for calculating what i forward
/// </summary>
class TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;
	Vector2D forward;
	Vector2D center;

	int speed = 3;
	int TAngle = 0;

	// defaults for collider
	int height = 32;
	int width = 32;
	int scale = 1;

	TransformComponent()
	{
		position.x = 0;
		position.y = 0;
	}

	TransformComponent(int sc)
	{
		position.x = 400;
		position.y = 320;

		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int  w, int sc)
	{
		position.x = x;
		position.y = y;

		height = h;
		width = w;
		scale = sc;
		SetCenter();
		SetForward();
	}

	void init() override
	{
		velocity.Zero(); //So that the ship stays still at the (re)start
	}

	/// <summary>
	/// Movement
	/// </summary>
	void update() override
	{
		position.x -= velocity.x * speed;
		position.y -= velocity.y * speed;
		WrapCoordinated(position.x, position.y, position.x, position.y);
	}

	/// <summary>
	/// Defines forward of the ship
	/// Used for forward movement 
	/// </summary>
	/// <param name="angle"></param>
	void UpdateForward(int angle)
	{
		float deg2Rad = (3.1415926535897f * 2.0f) / 360.0f;
		float rads = TAngle * deg2Rad;
		forward = Vector2D(sin(rads), cos(rads));
	}

	/// <summary>
	/// used to make the sprite match up with the transform 
	/// degrees vs radians etc..
	/// </summary>
	/// <param name="forward"></param>
	/// <returns></returns>
	float forwardToDegrees(Vector2D forward)
	{
		return (atan2(forward.y, forward.x) * (180 / M_PI)) - 90;
	}

	/// <summary>
	/// Normalizing a vector
	/// </summary>
	/// <param name="vector"></param>
	/// <returns></returns>
	Vector2D NormalizeVector2D(Vector2D vector)
	{
		float magnitude = sqrtf(vector.x * vector.x + vector.y * vector.y);
		return Vector2D(vector.x / magnitude, vector.y / magnitude);
	}

	/// <summary>
	/// Initial set of forward
	/// </summary>
	void SetForward()
	{
		forward.x = center.x + 16;
		forward.y = center.y;
	}

	/// <summary>
	/// Center of the transform
	/// used for forward vector
	/// </summary>
	void SetCenter()
	{
		center.x = position.x + 16;
		center.y = position.y + 16;
	}

	Vector2D GetCenter()
	{
		return center;
	}

	Vector2D GetForward()
	{
		return forward;
	}

	/// <summary>
	/// Wraps the coordinates so that you cannot move outside the game window
	/// Known issue that the ship can clippa at certain angles and teleport 
	/// to the otherside
	/// </summary>
	/// <param name="ix"></param>
	/// <param name="iy"></param>
	/// <param name="ox"></param>
	/// <param name="oy"></param>
	void WrapCoordinated(float ix, float iy, float& ox, float& oy)
	{
		ox = ix;
		oy = iy;
		if (ix < 0.0f - 32) ox = ix + 800.0f + 32;
		if (ix > 800.0f + 32) ox = ix - (800.0f + 32);
		if (iy < -32.0f) oy = iy + 640.0f + 32;
		if (iy > 640 + 32) oy = iy - 640.0f - 32;
	}
};