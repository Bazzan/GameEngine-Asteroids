#pragma once
/// <summary>
/// Makes use of tiles images for animation
/// </summary>
struct Animation
{

	int index;
	int frames;
	int speed; 


	Animation(){} //default
	Animation(int i, int f, int s)
	{
		index = i;
		frames = f;
		speed = s;
	}
};
