#pragma once
#include "Vehicle.h"
#include <InputHandler.h>

class Target : public Vehicle
{
private :
public :
	Target(float x, float y);

	void update();
	void draw(SDL_Renderer* renderer);

	void setLocation(Vector2D vec) { *location = vec; }
};