#include "Quaternion.h"

// Constructors
Quaternion::Quaternion()
{
	this->value[0] = this->value[1] = this->value[2] = 0; // i, j, k
	this->value[3] = 1;  // w
}

Quaternion::Quaternion(float i, float j, float k, float w)
{
	this->value[0] = i;
	this->value[1] = j;
	this->value[2] = k;
	this->value[3] = w;
}

Quaternion::Quaternion(const Vector3& vector, float w)
{
	this->value[0] = vector.GetX();
	this->value[1] = vector.GetY();
	this->value[2] = vector.GetZ();
	this->value[3] = w;

}

Quaternion::~Quaternion()
{
	delete[] value;
}


// Getters


float Quaternion::GetI() const { return this->value[0]; }
float Quaternion::GetJ() const { return this->value[1]; }
float Quaternion::GetK() const { return this->value[2]; }
float Quaternion::GetW() const { return this->value[3]; }


// Setters
void Quaternion::Set(float value[4])
{
	value = value;
}


void Quaternion::SetI(float i)
{
	this->value[0] = i;
}

void Quaternion::SetJ(float j)
{
	this->value[1] = j;
}

void Quaternion::SetK(float k)
{
	this->value[2] = k;
}

void Quaternion::SetW(float w)
{
	this->value[3] = w;
}


// Functions 

// normalize by multipling the quaternion by the inverse of its magnitude
void Quaternion::Normalized()
{

}

// Quaternion multiplication
Quaternion Quaternion::operator*(const Quaternion& other)
{
	return Quaternion(	GetJ() * other.GetK() - GetK() * other.GetJ() + GetI() * other.GetW() + GetW() * other.GetI(),
						GetK() * other.GetI() - GetI() * other.GetK() + GetJ() * other.GetW() + GetW() * other.GetJ(),
						GetI() * other.GetJ() - GetJ() * other.GetI() + GetK() * other.GetW() + GetW() * other.GetK(),
						GetW() * other.GetW() - GetI() * other.GetI() - GetJ() * other.GetJ() - GetK() * other.GetK()	);
}


// Rotate the quaternion by a vector : multiply this by q = (0, dx, dy, dz)
void Quaternion::RotateByVector(const Vector3& vector)
{

}

// Apply the quaternion update by the angular velocity
void Quaternion::UpdateByAngularVelocity(const Vector3& rotation, float duration)
{

}

// Convert Euler Vector3 to Quaternion
Quaternion Quaternion::EulerToQuaternion(const Vector3& vector)
{
	return Quaternion();
}




