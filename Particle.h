#pragma once

#include "Core.h"

typedef float real;

class Particle
{
private:

	real mass;

	Vector2d position;

	Vector2d velocity;

	real dampingValue;

	//Holds all forces to be applied to the next iteration step only
	Vector2d forceAccumulated;

public:

	real getDampingValue() const
	{
		return dampingValue;
	}

	real getMass() const
	{
		return mass;
	}

	Vector2d getPosition() const
	{
		return position;
	}

	Vector2d getVelocity() const
	{
		return velocity;
	}

	Vector2d getAccumForces() const
	{
		return forceAccumulated;
	}

	void setDampingValue(float& value)
	{
		dampingValue = value;
	}

	void setMass(real& value)
	{
		mass = value;
	}

	void setPosition(Vector2d& pos)
	{
		position = pos;
	}

	void setVelocity(Vector2d& vec)
	{
		velocity = vec;
	}

	Particle()
	{
		velocity = { 0.0f, 0.0f };
		position = { 0.0f, 0.0f };

		mass = 1.0f;
		dampingValue = 0.5f;
	}

	Particle(Vector2d initPos, Vector2d& initVel, real& dampingVal, real& m)
	{
		setPosition(initPos);
		setVelocity(initVel);

		dampingValue = dampingVal;
		mass = m;
	}

	//Calculate the position and velocity with respect to time
	void integrate(real& duration, real& stepSize, Vector2d& acc);

	//------------------------------------------------------------

	//Solving the ODE to get acceleration 
	Vector2d findAcceleration();

	//Calculating velocity with our found value of acceleration
	Vector2d calculateVelocity(Vector2d& initVelocity, real& h, Vector2d& acceleration);

	//Solving the equation of motion to find position
	Vector2d positionUpdate(Vector2d& initPosition, Vector2d& initVelocity, float& h);

	void RK4(float& time, real& h);

	void addForce(const Vector2d& force);
	//This clearsall forces applied to the particle and will be called after each integration step.
	void clearAccumulatedForces();

};

