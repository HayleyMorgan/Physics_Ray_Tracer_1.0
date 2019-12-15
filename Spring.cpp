#include "pch.h"
#include "Spring.h"
#include <vector>


Spring::Spring()
{

}

Spring::Spring(real& springConstant, real& restLength) : springConstant(springConstant), restLength(restLength)
{
}

Spring::Spring(real& springConstant, real& restLength, Particle* p, Particle* p2) : springConstant(springConstant), restLength(restLength), p_particle(p), p_particle2(p2)
{
}

//Added for calculating the same thing with particle pointers
void Spring::calculateSpringForce()
{
	Vector2d d;
	real vec_d_magnitude;
	Vector2d normalised_d;
	Vector2d finalSpringForce;

	d = p_particle2->getPosition() - p_particle->getPosition();

	vec_d_magnitude = d.magintude();

	normalised_d = d * (1.0f / vec_d_magnitude);

	//finalSpringForce = -k (|vec_d| - L) * normalised_vec_d
	finalSpringForce = normalised_d * (-springConstant) * (vec_d_magnitude - restLength);

	//Adding the force to the first particle
	p_particle2->addForce(finalSpringForce);

	//Add the same force in the opposite direction to particle on the other end of the spring
	finalSpringForce.negate();
	p_particle->addForce(finalSpringForce);

	Vector2d relitiveVelocity1 = p_particle->getVelocity() - p_particle2->getVelocity();
	Vector2d finalDampingForce1;
	
	real vel_mag = relitiveVelocity1.magintude();
	
	if (vel_mag > 0)
	{
		Vector2d normalised_vel = relitiveVelocity1 / vel_mag;
		finalDampingForce1 = normalised_vel * (-p_particle->getDampingValue());
	}
	else
	{
		finalDampingForce1 = { 0.0f, 0.0f };
	}
	
	p_particle->addForce(finalDampingForce1);

}

void Spring::calculateSpringForce(Particle* particles, int& i)
{
	Vector2d d;
	real vec_d_magnitude;
	Vector2d normalised_d;
	Vector2d finalSpringForce;

	if (i != 0)
	{
		int prevIndex = i - 1;
		d = particles[i].getPosition() - particles[prevIndex].getPosition();
	}

	vec_d_magnitude = d.magintude();

	normalised_d = d * (1 / vec_d_magnitude);

	//finalSpringForce = -k (|vec_d| - L) * normalised_vec_d
	finalSpringForce = normalised_d * (-springConstant) * (vec_d_magnitude - restLength);

	//Adding the force to the first particle
	particles[i].addForce(finalSpringForce);

	//Add the same force in the opposite direction to particle on the other end of the spring
	finalSpringForce.negate();
	particles[i-1].addForce(finalSpringForce);

	Vector2d relitiveVelocity1 = particles[1].getVelocity() - particles[0].getVelocity();
	Vector2d finalDampingForce1;
	
	real vel_mag = relitiveVelocity1.magintude();
	
	if (vel_mag > 0)
	{
		Vector2d normalised_vel = relitiveVelocity1 / vel_mag;
		finalDampingForce1 = normalised_vel * (-particles[i].getDampingValue());
	}
	else
	{
		finalDampingForce1 = { 0.0f, 0.0f };
	}
	
	particles[i].addForce(finalDampingForce1);
	
}
