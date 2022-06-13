#include "Walker.h"
#include <InputHandler.h>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dis_width(0.0f, 640.0f);
std::uniform_real_distribution<float> dis_height(0.0f, 480.0f);

Walker::Walker(int x, int y) 
{
	target = new Target(dis_width(gen), dis_height(gen));
	hunter = new Vehicle(dis_width(gen), dis_height(gen));
	//enemy = new Vehicle(dis_width(gen), dis_height(gen));

	hideTarget = new Vector2D(0.0f, 0.0f);
	steering = new Vector2D(0.0f, 0.0f);
}
//Vector2D hide(const Vehicle* hunter, const vector<>& obstacles);
void Walker::update() 
{
	target->setLocation(InputHandler::Instance()->getMousePosition());
	steering = hunter->pursue(target);
	hunter->applyForce(steering);
	/*
	*hideTarget = hide(hunter, enemy - 관련있었음);
	enemy->applyForce(hideTarget);
	enemy->update();
	*/
	target->update();
	hunter->update();
}

void Walker::draw(SDL_Renderer* renderer)
{
	target->draw(renderer);
	hunter->draw(renderer);
}