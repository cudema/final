#pragma once
#include <Vector2D.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>

class Vehicle
{
private :
	Vector2D* target;
	Vector2D* prediction;
	Vector2D* force;

	Vector2D* tr_xy1;
	Vector2D* tr_xy2;
	Vector2D* tr_xy3;

	//double maxDouble;

	float maxSpeed;
	float maxForce;
	float radian;
	float r;
protected :
	Vector2D* location;
	Vector2D* velocity;
	Vector2D* accelaration;
public :
	Vehicle();
	Vehicle(float x, float y);

	enum Deceleration {slow = 1, normal = 2, fast = 3};

	Vector2D rotation(float x, float y);
	Vector2D arrive(Vector2D* TargetPos, Deceleration deceleration);
	//Vector2D hide(const Vehicle* hunter, const vector<>& obstacles);
	Vector2D getHidePosition(const Vector2D& posOb, const double radiusOb, const Vector2D& posHunter);
	Vector2D* pursue(Vehicle* vehicle);
	Vector2D* seek(Vector2D* target);

	void applyForce(Vector2D* Force);
	void update();
	void draw(SDL_Renderer* renderer);

	Vector2D getLocation() { return *location; }
	Vector2D getVelocity() { return *velocity; }
};