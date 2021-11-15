#include "Quaternion.h"

// Constructors
Quaternion::Quaternion()
{
	this->i = this->j = this->k = 0; // i, j, k
	this->w = 1;  // w
}

Quaternion::Quaternion(float i, float j, float k, float w)
{
	this->i = i;
	this->j = j;
	this->k = k;
	this->w = w;
}

Quaternion::Quaternion(const Vector3& vector, float w)
{
	this->i = vector.GetX();
	this->j = vector.GetY();
	this->k = vector.GetZ();
	this->w = w;

}

Quaternion::~Quaternion()
{
	delete[] value;
}


// Getters


float Quaternion::GetI() const { return this->i; }
float Quaternion::GetJ() const { return this->j; }
float Quaternion::GetK() const { return this->k; }
float Quaternion::GetW() const { return this->w; }


// Setters
void Quaternion::Set(float value[4])
{
	value = value;
}


void Quaternion::SetI(float i)
{
	this->i = i;
}

void Quaternion::SetJ(float j)
{
	this->j = j;
}

void Quaternion::SetK(float k)
{
	this->k = k;
}

void Quaternion::SetW(float w)
{
	this->w = w;
}


// Functions 

// normalize by multipling the quaternion by the inverse of its magnitude
void Quaternion::Normalized()
{

}

// Quaternion multiplication
Quaternion Quaternion::operator*(const Quaternion& other)
{
	return {	GetJ() * other.GetK() - GetK() * other.GetJ() + GetI() * other.GetW() + GetW() * other.GetI(),
						GetK() * other.GetI() - GetI() * other.GetK() + GetJ() * other.GetW() + GetW() * other.GetJ(),
						GetI() * other.GetJ() - GetJ() * other.GetI() + GetK() * other.GetW() + GetW() * other.GetK(),
						GetW() * other.GetW() - GetI() * other.GetI() - GetJ() * other.GetJ() - GetK() * other.GetK()	};
}


// Rotate the quaternion by a vector - multiply this by q = (0, dx, dy, dz)
void Quaternion::RotateByVector(const Vector3& vector)
{

}

// Apply the quaternion update by the angular velocity
void Quaternion::UpdateByAngularVelocity(const Vector3& rotation, float duration)
{

}

// Convert Euler Vector3 to Quaternion
Quaternion Quaternion::EulerToQuaternion(const Vector3& euler)
{
	float c1 = cos(euler.GetZ() * 0.5f);
	float c2 = cos(euler.GetY() * 0.5f);
	float c3 = cos(euler.GetX() * 0.5f);
	float s1 = sin(euler.GetZ() * 0.5f);
	float s2 = sin(euler.GetY() * 0.5f);
	float s3 = sin(euler.GetX() * 0.5f);


	return {c1 * c2 * s3 - s1 * s2 * c3,
					  c1 * s2 * c3 + s1 * c2 * s3,
					  s1 * c2 * c3 - c1 * s2 * s3,
					  c1 * c2 * c3 + s1 * s2 * s3};

}




