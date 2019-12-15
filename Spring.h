#pragma once

typedef float real;
#include "Core.h"
#include "Particle.h"
#include <vector>

class Spring
{
private:

	real springConstant;

	real restLength;

	Particle* p_particle;
	Particle* p_particle2;

public:

	Spring();

	Spring(real& springConstant, real& restLength);
	
	//Constructor with Particle objects
	Spring(real& springConstant, real& restLength, Particle* p, Particle* p2);

	real getSpringConstant() const
	{
		return springConstant;
	}

	real getRestLength()
	{
		return restLength;
	}

	void setSpringConst(real k)
	{
		springConstant = k;
	}

	void setRestLength(real restL)
	{
		restLength = restL;
	}


	void calculateSpringForce(Particle* particles, int& i);

	void calculateSpringForce();

};