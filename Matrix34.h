#pragma once

#include "Vector3.h"
#include "Quaternion.h"

class Matrix34
{
private:
	// value of the Matrix 3X4
	//float values[12];

	union {
		struct { float l1[4], l2[4], l3[4]; };
		float values[12];
	};

public:
	Matrix34();
	Matrix34(float value[12]);
	Matrix34(const Matrix34& matrix34);
	~Matrix34();

	float* Get() const;
	void Set(float value[12]);

	// Combination of the linear transformation
	Matrix34 operator*(const Matrix34& other) const;

	// Transform of a vector
	Vector3 operator*(const Vector3& vector) const;

	// Get the Inverse matrix
	Matrix34 Inverse();

	// Set the matrix base on a quaternion and a position
	void SetOrientationAndPosition(const Quaternion& q, const Vector3& p);

	// Transform a position
	Vector3 TransformPosition(const Vector3& vector);

	// Transform a direction by ignoring the translation
	Vector3 TransformDirection(const Vector3& vector);
};

