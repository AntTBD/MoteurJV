#pragma once

#include "Vector3.h"
#include "Quaternion.h"

class Matrix33
{
private:
	// value of the Matrix 3X3
	//float values[9];

	union {
		struct { float l1[3], l2[3], l3[3]; };
		float values[9];
	};
public:
	Matrix33();
	Matrix33(float value[9]);
	Matrix33(const Matrix33& matrix33);
	~Matrix33();

	float* Get() const;
	void Set(float value[9]);

	// Combination of the linear transformation
	Matrix33 operator*(const Matrix33& other) const;

	// Transform of a vector
	Vector3 operator*(const Vector3& vector) const;

	// Get the Inverse matrix
	Matrix33 Inverse();

	// Get the Transpose matrix
	Matrix33 Transpose();

	// Set the matrix base on a quaternion
	void SetOrientation(const Quaternion& q);
};

