#pragma once

#include "Vector3.h"


class Quaternion
{
private:
	// w, i, j, k
	//float value[4];

	// union c++ exemple : https://stackoverflow.com/questions/6338645/named-structures-in-c-unions
	union {
		struct { float  i, j, k, w; };
		float value[4];
	};


public:
	Quaternion();
	Quaternion(float i, float j, float k, float w);
	Quaternion(float value[4]);
	Quaternion(const Vector3& vector, float w);
	Quaternion(const Quaternion& quaternion);
	~Quaternion();

	float* Get() const; // return tab[4] ???
	float GetI() const;
	float GetJ() const;
	float GetK() const;
	float GetW() const;
	void Set(float value[4]);
	void SetW(float w);
	void SetI(float i);
	void SetJ(float j);
	void SetK(float k);


	// normalize by multipling the quaternion by the inverse of its magnitude
	void Normalized();

	// Quaternion multiplication
	Quaternion operator*(const Quaternion& other);

	// Rotate the quaternion by a vector - multiply this by q = (0, dx, dy, dz)
	void RotateByVector(const Vector3& vector);

	// Apply the quaternion update by the angular velocity
	void UpdateByAngularVelocity(const Vector3& rotation, float duration);

	// Convert Euler Vector3 to Quaternion
	Quaternion EulerToQuaternion(const Vector3& euler);
};

