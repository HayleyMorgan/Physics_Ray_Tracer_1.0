#pragma once
typedef float real;

class Vector2d
{
private:

public:

	real x;
	real y;

	//default constructor  
	Vector2d() : x(0), y(0) {};
	//Explicit Constructor, assigns values to the vector
	Vector2d(const real x, const real y) : x(x), y(y) {};

	void negate()
	{
		x = -x;
		y = -y;
	}

	real magintude() const;

	real sqaureMagnitude() const;

	void nomaliseVector();

	void operator*=(const real& rhs);

	void operator/=(const real& rhs); 

	Vector2d operator/(const real& rhs);

	Vector2d operator*(const real& rhs);

	void operator+=(const Vector2d& other)
	{
		x += other.x;
		y += other.y;
	}

	Vector2d operator+=(const Vector2d& other) const
	{
		return Vector2d(x + other.x, y + other.y);
	}

	void operator-=(const Vector2d& other)
	{
		x -= other.x;
		y -= other.y;
	}

	Vector2d operator+(const Vector2d& other)
	{
		return Vector2d(x + other.x, y + other.y);
	}

	//Return a vector with subtracted components
	Vector2d operator-(const Vector2d& other)
	{
		return Vector2d(x - other.x, y - other.y);
	}

	//If this vector is multipied by another vector, the * operator will automatically return the dot product of those two vectors
	//..Not a componentwise multiplication
	real operator*(const Vector2d& other) const
	{
		return x * other.x + y * other.y;
	}

	Vector2d operator+(const real& other)
	{
		return Vector2d(x + other, y + other);
	}

	Vector2d operator-(const real& rhs)
	{
		return Vector2d(x - rhs, y - rhs);
	}

	//Scaling the vector and adding 
	void addScaledVector(const Vector2d& vector, const real scaleFactor)
	{
		x += vector.x * scaleFactor;
		y += vector.y * scaleFactor;
	}

	//Method for adding two vectors together component wise - You will get a vector as the result
	Vector2d vectorComponentProd(const Vector2d& vector)
	{
		return Vector2d(x * vector.x, y * vector.y);
	}

	//Modifies this vector instead of creating an additional vector
	void VectorProductUpdate(const Vector2d& vector)
	{
		x *= vector.x;
		y *= vector.y;
	}

	real dotProduct(const Vector2d& vector)
	{
		VectorProductUpdate(vector);
		return(x + y);
	}


	void clear();

};