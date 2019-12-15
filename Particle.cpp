#include "pch.h"

#include "Particle.h"
#include "math.h"

void Particle::integrate(real& duration, real& stepSize, Vector2d& acc)
{
	clearAccumulatedForces();
}

//The accumulation stage has to be completed before the particle is integrated
void Particle::addForce(const Vector2d& force)
{
	forceAccumulated += force;
}

void Particle::clearAccumulatedForces()
{
	forceAccumulated.clear();
}


//Old RK4 which runs but is bugged
//void Particle::RK4(float& time, real& h)
//{
//	Vector2d k1, k2, k3, k4;
//
//	Vector2d initVelocity = velocity;
//
//	float t0 = time;
//
//	//-----------------------------------------------------------
//	//First calculation of velocity
//	k1 = f(initVelocity, t0) * h;
//
//	//-----------------------------------------------------------
//
//	Vector2d newVel1 = initVelocity + k1 * 0.5;
//
//	time = t0 + h / 2;
//
//	k2 = f(newVel1, time) * h;
//
//	//-----------------------------------------------------------
//
//	Vector2d newVel2 = getVelocity() + k2 * 0.5;
//
//	k3 = f(newVel2, time) * h;
//
//	//-----------------------------------------------------------
//	Vector2d newVel3 = getVelocity() + k3;
//	
//	time = t0 + h / 2;
//
//	k4 = f(newVel3, time) * h;
//
//	//-----------------------------------------------------------
//
//	Vector2d finalK = (k1 + k2 * 2 + k3 * 2 + k4) / 6;
//	Vector2d finalVel1 = initVelocity + finalK;
//	setVelocity(finalVel1);
//}


void Particle::RK4(float& time, real& h)
{
	//Where does the variable time get taken into consideration?
	Vector2d initPosition = getPosition();
	Vector2d initVelocity = getVelocity();

	Vector2d acceleration = findAcceleration();

	//These are simply the first calulations without a step.
	//Warning: I have put time here... Is this correct?
	Vector2d pos_k1 = positionUpdate(initPosition, initVelocity, time);
	Vector2d vel_k1 = calculateVelocity(initVelocity, time, acceleration);

	//--------------------------------------//
	//Create a spring object here to calculate the forces depending on the position and velocity of the particle

	acceleration = findAcceleration();

	real stepSize = h * 0.5;

	Vector2d pos_k2 = positionUpdate(initPosition, initVelocity, stepSize);

	Vector2d vel_k2 = calculateVelocity(initVelocity, stepSize, acceleration);

	//-------------------------------------//

	//Then we iterate again

	//acceleration = findAcceleration(); // <- this should be based on the velocity and position we just found

	Vector2d pos_k3 = positionUpdate(initPosition, initVelocity, stepSize);

	//Warning: Velocity will be the same in this case because acceleration is not updated.
	Vector2d vel_k3 = calculateVelocity(initVelocity, stepSize, acceleration);

	//-------------------------------------//

	//acceleration = findAcceleration();

	//(Now using h, not stepSize = 0.5 * h)
	Vector2d pos_k4 = positionUpdate(initPosition, initVelocity, h);

	//Velocity will change here, because of h is a full step forward
	Vector2d vel_k4 = calculateVelocity(initVelocity, h, acceleration);

	//-----------------------------------//
	//Again, this currently doesn't change because the fore is not being updated with position and time
	//acceleration = findAcceleration();

	Vector2d finalPosition = initPosition + (pos_k1 + pos_k2 * 2 + pos_k3 * 2 + pos_k4) * (h / 6);

	setPosition(finalPosition);

	Vector2d finalVelocity = initVelocity + (vel_k1 + vel_k2 * 2 + vel_k3 * 2 + vel_k4) * (h / 6);

	setVelocity(finalVelocity);
}



//Solving the ODE to get velocity 
Vector2d Particle::findAcceleration()
{
	Vector2d particle_acceleration = { 0.0, 0.0 };

	//I feel like calculating the forces should be here...?
	//or should acceleration stay the same for each iteration

	particle_acceleration = getAccumForces() / mass;

	return particle_acceleration;
}

//Calculating velocity with our new value of acceleration
Vector2d Particle::calculateVelocity(Vector2d& initVelocity, real& h, Vector2d& acceleration)
{
	Vector2d particle_velocity = initVelocity + acceleration * h;
	setVelocity(particle_velocity);
	return particle_velocity;
}

Vector2d Particle::positionUpdate(Vector2d& initPosition, Vector2d& initVelocity, float& h)
{
	Vector2d pos = initPosition + (initVelocity + getVelocity()) * h * 0.5;
	setPosition(pos);
	return pos;
}

//-------------------------------------------------------------//
