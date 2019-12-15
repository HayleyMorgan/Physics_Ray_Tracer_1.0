#include "pch.h"
#include "Core.h"
#include <math.h>

#define real_sqrt sqrtf

real Vector2d::magintude() const
{
	return real_sqrt(x * x + y * y);
}

//Returns the squared magnituded of the vector
//Less computationally expensive alternative mag
real Vector2d::sqaureMagnitude() const
{
	return x * x + y * y;
}

void Vector2d::nomaliseVector()
{
	real l = magintude();
	if (l > 0)
	{
		(*this) *= ((real)1) / l;
	}
}

//The normaliseVector() uses this overload 
void Vector2d::operator*=(const real& rhs)
{
	//This is modifying this particlular vector if it's on the LHS of the *= 
	x *= rhs;
	y *= rhs;
}

void Vector2d::operator/=(const real& rhs)
{
	//This is modifying this particlular vector if it's on the LHS of the *= 
	x /= rhs;
	y /= rhs;
}

Vector2d Vector2d::operator/(const real& rhs)
{
	return Vector2d(x/rhs, y/rhs);
}

//Retuns a copy of the vector scales to a given value
Vector2d Vector2d::operator*(const real& rhs)
{
	return Vector2d(x*rhs, y*rhs);
}

void Vector2d::clear()
{
	this->x = 0.0f;
	this->y = 0.0f;
}