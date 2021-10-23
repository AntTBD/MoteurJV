#include <math.h>
#include <assert.h>
#include "Vector3.h"

// Constructors
Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
}

Vector3::Vector3(const Vector3& vector)
{
	this->x = vector.GetX();
	this->y = vector.GetY();
	this->z = vector.GetZ();
}

// Operators overload
Vector3& Vector3::operator=(const Vector3& vector)
{
	this->x = vector.GetX();
	this->y = vector.GetY();
	this->z = vector.GetZ();
	return *this;
}

Vector3 Vector3::operator+(const Vector3& vector) const
{
	return Vector3(this->x + vector.GetX(), this->y + vector.GetY(), this->z + vector.GetZ());
}

Vector3& Vector3::operator+=(const Vector3& vector)
{
	this->x += vector.GetX();
	this->y += vector.GetY();
	this->z += vector.GetZ();
	return *this;
}

Vector3 Vector3::operator-(const Vector3& vector) const
{
	return Vector3(this->x - vector.GetX(), this->y - vector.GetY(), this->z - vector.GetZ());
}

Vector3& Vector3::operator-=(const Vector3& vector)
{
	this->x -= vector.GetX();
	this->y -= vector.GetY();
	this->z -= vector.GetZ();
	return *this;
}

Vector3 Vector3::operator*(float value) const
{
	return Vector3(this->x * value, this->y * value, this->z * value);
}

Vector3& Vector3::operator*=(float value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	return *this;
}

Vector3 Vector3::operator/(float value) const
{
	assert(value != 0);
	return Vector3(this->x / value, this->y / value, this->z / value);
}

Vector3& Vector3::operator/=(float value)
{
	assert(value != 0);
	this->x /= value;
	this->y /= value;
	this->z /= value;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector3& vector)
{
	os << "(" << vector.GetX() << "," << vector.GetY() << "," << vector.GetZ() << ")";
	return os;
}

// Getters and Setters
float Vector3::GetX() const
{
	return this->x;
}

float Vector3::GetY() const
{
	return this->y;
}

float Vector3::GetZ() const
{
	return this->z;
}

void Vector3::SetX(float _x)
{
	this->x = _x;
}

void Vector3::SetY(float _y)
{
	this->y = _y;
}

void Vector3::SetZ(float _z)
{
	this->z = _z;
}

// Functions
float Vector3::DotProduct(const Vector3& vector) const
{
	return this->x * vector.GetX() + this->y * vector.GetY() + this->z * vector.GetZ();
}

Vector3 Vector3::CrossProduct(const Vector3& vector) const
{
	return Vector3(this->y * vector.GetZ() - this->z * vector.GetY(), this->z * vector.GetX() - this->x * vector.GetZ(), this->x * vector.GetY() - this->y * vector.GetX());
}

float Vector3::Magnitude() const
{
	return float(sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
}

float Vector3::SquaredMagnitude() const // Squared magnitude is less taxing to calculate and is often enough for what we want to do
{
	return float(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

Vector3& Vector3::Normalize() // Make the vector length to 1
{
	float length = this->Magnitude();
	assert(length != 0);
	*this /= length;
	return *this;
}

Vector3& Vector3::SetZero() // Set vector to (0, 0, 0)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	return *this;
}