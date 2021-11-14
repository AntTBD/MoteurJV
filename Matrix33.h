#pragma once

#include "Vector3.h"
#include "Quaternion.h"

class Matrix33
{
private:
	// value of the Matrix 3X3
	union {
		struct { float l1[3], l2[3], l3[3]; };
		float values[9];
	};
public:
	Matrix33();
	Matrix33(float value[9]);
	Matrix33(float _l1[3], float _l2[3], float _l3[3]);
	Matrix33(const Matrix33& matrix33);
	~Matrix33() = default;

	float* Get() const;
	float Get(int index) const;
	void Set(float value[9]);

	Matrix33& operator=(const Matrix33& other);

	// Combination of the linear transformation
	Matrix33 operator*(const Matrix33& other) const;

	// Transform of a vector
	Vector3 operator*(const Vector3& vector) const;

	// Assign operator
	float* operator[](int index);

	// Get the Transpose matrix
	Matrix33 Transpose();

	// Get the Inverse matrix
	Matrix33 Inverse();

	// Set the matrix base on a quaternion
	void SetOrientation(const Quaternion& q);
};

std::ostream& operator<< (std::ostream& os, const Matrix33& matrix33);

Matrix33 operator*(const Matrix33& mat, const float value);
Matrix33 operator*(const float value, const Matrix33& mat);