#pragma once

#include "main.h"
#include "Vector2D.h"
#include "Vehicle.h"
#include "Target.h"

class Walker 
{
private :
	Vehicle* target;
	Vehicle* hunter;

	Vector2D* hideTarget;
public:
  Walker(int x, int y);
  void draw(SDL_Renderer* renderer);
  void update();
};