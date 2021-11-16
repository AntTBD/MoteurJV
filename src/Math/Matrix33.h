#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include <vector>
#include <assert.h>

class Matrix33
{
private:
	// value of the Matrix 3X3
	std::vector<float> values;
public:
	Matrix33();
	Matrix33(std::vector<float> value);
	Matrix33(const Matrix33& matrix33);
	~Matrix33();

	std::vector<float> Get() const;
	float Get(int index) const;
	void Set(std::vector<float> value);

	Matrix33& operator=(const Matrix33& other);

	// Combination of the linear transformation
	Matrix33 operator*(const Matrix33& other) const;

	// Transform of a vector
	Vector3 operator*(const Vector3& vector) const;

	// Assign operator
	std::vector<float> operator[](int index);

	// Transform a position
	Vector3 TransformPosition(const Vector3& vector);

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