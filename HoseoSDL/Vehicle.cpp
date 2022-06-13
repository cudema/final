#include "Vehicle.h"
#define min(x, y) x < y ? x : y

Vehicle::Vehicle()
{

}

Vehicle::Vehicle(float x, float y)
{
	location = new Vector2D(x, y);
	velocity = new Vector2D(0.0f, 0.0f);
	accelaration = new Vector2D(0.0f, 0.0f);

	target = new Vector2D(0.0f, 0.0f);
	prediction = new Vector2D(0.0f, 0.0f);
	force = new Vector2D(0.0f, 0.0f);

	tr_xy1 = new Vector2D(0.0f, 0.0f);
	tr_xy2 = new Vector2D(0.0f, 0.0f);
	tr_xy3 = new Vector2D(0.0f, 0.0f);

	maxSpeed = 4.0f;
	maxForce = 0.25f;
	radian = 0.0f;
	r = 16.0f;
}

void Vehicle::applyForce(Vector2D* Force)
{
	*accelaration += *Force;
}

Vector2D Vehicle::rotation(float x, float y)
{
	Vector2D tmp(0.0f, 0.0f);

	tmp.setX(cos(radian) * x - sin(radian) * y);
	tmp.setY(sin(radian) * x + cos(radian) * y);

	return tmp;
}

Vector2D Vehicle::arrive(Vector2D* TargetPos, Deceleration deceleration)
{
	Vector2D ToTarget = *TargetPos - *location;

	double dist = ToTarget.length();

	if (dist > 0)
	{
		const double DecelerationTweaker = 0.3;
		double speed = dist / ((double)deceleration * DecelerationTweaker);

		speed = min(speed, maxSpeed);

		Vector2D DisiredVelocity = ToTarget * speed / dist;

		return (DisiredVelocity - *velocity);
	}

	return Vector2D(0.0f, 0.0f);
}

Vector2D* Vehicle::seek(Vector2D* target)
{
	*force = *target - *location;
	force->normalize();
	*force *= maxSpeed;

	*force -= *velocity;
	force->limit(maxForce);

	applyForce(force);

	return force;
}

Vector2D* Vehicle::flee(Vector2D target)
{
	Vector2D desiredVelocity = *location - target * maxSpeed;
	desiredVelocity.normalize();

	return new Vector2D(desiredVelocity - *velocity);
}

Vector2D* Vehicle::evade(Vehicle* vehicle)
{
	Vector2D toPursuer = vehicle->getLocation() - *location;

	const double threatRange = 100.0f;

	if (toPursuer.length() > threatRange * threatRange)
		return new Vector2D(0.0f, 0.0f);

	double lookAheadTime = toPursuer.length() / (maxSpeed + velocity->length());

	return flee(vehicle->getLocation() + vehicle->getVelocity() * lookAheadTime);
}

Vector2D* Vehicle::pursue(Vehicle* vehicle)
{
	*target = vehicle->getLocation();
	*prediction = vehicle->getVelocity();

	*prediction *= 20.0f;
	*target += *prediction;

	return seek(target);
}

/* 외웠던 것 - 2:50
Vector2D Vehicle::hide(const Vehicle* hunter, const vector<>& obstacles)
{
	double distToClosest = maxDouble;
	Vector2D bestHidingSpot;

	?
	?

	while(? != obstacles.end())
	{
		Vecotr2D hidingSpot = getHidePosition(오브젝트 위치, 오브젝트 반지름, hunter->getLocation());

		double dist = ?;

		if(dist < distToClosest)
		{
			distToClosest = dist;
			bestHidingSpot = hidingSpot;
			closest = ?;
		}

		++?
	}

	if(distToClosest == maxFloat)
	{
		return evade(hunter);
	}

	return arrive(*bestHidingSpot, fast);
}
*/

Vector2D Vehicle::getHidePosition(const Vector2D& posOb, const double radiusOb, const Vector2D& posHunter)
{
	const double distFromBoundary = 30.0f;
	double distAway = radiusOb + distFromBoundary;

	Vector2D toOb = posOb - posHunter;
	toOb.normalize();

	return (toOb * distAway) + posOb;
}

void Vehicle::update()
{
	radian = atan2(velocity->getY(), velocity->getX());

	*tr_xy1 = rotation(-r, -r / 2);
	*tr_xy2 = rotation(-r, r / 2);
	*tr_xy3 = rotation(r, 0.0f);

	*velocity += *accelaration;
	velocity->limit(maxSpeed);
	*location += *velocity;
	*accelaration *= 0.0f;
}

void Vehicle::draw(SDL_Renderer* renderer)
{
	filledTrigonColor(renderer,
		location->getX() + tr_xy1->getX(),
		location->getY() + tr_xy1->getY(),
		location->getX() + tr_xy2->getX(),
		location->getY() + tr_xy2->getY(),
		location->getX() + tr_xy3->getX(),
		location->getY() + tr_xy3->getY(), 0xFFFFFFFF);
}