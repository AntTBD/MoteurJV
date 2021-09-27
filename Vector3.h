#pragma once
#include <iostream>

class Vector3
{
private:
	float x, y, z;

public:
	// Constructors
	Vector3();
	Vector3(float _x, float _y, float _z);
	Vector3(const Vector3& vector);

	// Operators
	Vector3& operator=(const Vector3& vector);
	Vector3 operator+(const Vector3& vector) const;
	Vector3& operator+=(const Vector3& vector);
	Vector3 operator-(const Vector3& vector) const;
	Vector3& operator-=(const Vector3& vector);
	Vector3 operator*(float value) const;
	Vector3& operator*=(float value);
	Vector3 operator/(float value) const;
	Vector3& operator/=(float value);

	// Getters / Setters
	float GetX() const;
	float GetY() const;
	float GetZ() const;
	void SetX(float _x);
	void SetY(float _y);
	void SetZ(float _z);

	// Functions
	float DotProduct(const Vector3& vector) const;
	Vector3 CrossProduct(const Vector3& vector) const;
	float Magnitude() const;
	float SquaredMagnitude() const;
	Vector3& Normalize();
	Vector3& SetZero();

};

// << operator
std::ostream& operator<< (std::ostream& os, const Vector3& vector);