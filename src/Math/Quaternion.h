#pragma once

#define _USE_MATH_DEFINES // include M_PI
#include "Vector3.h"
#include <vector>
#include <assert.h>
#include <algorithm>
#include <cmath>



class Quaternion
{
private:
	// w, i, j, k
	//float value[4];

	// union c++ exemple : https://stackoverflow.com/questions/6338645/named-structures-in-c-unions
	union {
		struct {float  w, i, j, k ; };

		float value[4];
	};


public:
	Quaternion();
	Quaternion(float w, float i, float j, float k);
	Quaternion(std::vector<float> value);
    Quaternion(float value[4]);
	Quaternion(const Vector3& vector, float w);
	Quaternion(const Quaternion& quaternion);
	~Quaternion();

	std::vector<float> Get() const; // return tab[4] ???
	float GetW() const;
	float GetI() const;
	float GetJ() const;
	float GetK() const;
	
	void Set(std::vector<float> value);
	void SetW(float w);
	void SetI(float i);
	void SetJ(float j);
	void SetK(float k);


	
// Operators
    Quaternion& operator=(const Quaternion& other);
	Quaternion operator+(const Quaternion& other) const;
	Quaternion& operator+=(const Quaternion& other);
	Quaternion operator*(const Quaternion& other) const;
	Quaternion& operator*=(const Quaternion& other);
	Quaternion& operator*=(float val);
	Quaternion operator*(float val) const;

    // * operator dans les 2 sens
    friend Quaternion operator*(float value, const Quaternion& quaternion);




	// normalize by multipling the quaternion by the inverse of its magnitude
	void Normalize();
	Quaternion Normalized() const;

	Quaternion Conjugate() const;

	// Rotate the quaternion by a vector - multiply this by q = (0, dx, dy, dz)
	void RotateByVector(const Vector3& vector);
	Quaternion RotatedByVector(const Vector3& vector) const;

	// Apply the quaternion update by the angular velocity
    // this += this->RotateByVector(rotation) * duration
	void UpdateByAngularVelocity(const Vector3& rotation, float duration);

	// Convert Euler Vector3 to Quaternion
	static Quaternion EulerToQuaternion(const Vector3& euler);
    static Quaternion EulerInDegreesToQuaternion(const Vector3& euler);

    // Convert Quaternion to Euler Vector3
    // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    Vector3 ToEuler() const;
    Vector3 ToEulerInDegrees() const;




	std::string toString() const;

	friend std::ostream& operator<< (std::ostream& os, const Quaternion& quaternion);

};

