#include "Target.h"

Target::Target(float x, float y)
{
	location = new Vector2D(x, y);
	velocity = new Vector2D(0.0f, 0.0f);
	accelaration = new Vector2D(0.0f, 0.0f);
}

void Target::update()
{
	location = InputHandler::Instance()->getMousePosition();
}

void Target::draw(SDL_Renderer* renderer)
{
	filledCircleColor(renderer, location->getX(), location->getY(), 10, 0xFFFF0000);
}