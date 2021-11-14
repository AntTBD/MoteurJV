#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix33.h"

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
	Matrix34(float _l1[4], float _l2[4], float _l3[4]);
	Matrix34(const Matrix34& matrix34);
	Matrix34(const Matrix33& matrix33, const Vector3& vec);
	~Matrix34() = default;

	float* Get() const;
	float Get(int index) const;
	Matrix33 GetMatrix33() const;
	Vector3 GetVector() const;

	void Set(float value[12]);

	Matrix34& operator=(const Matrix34& other);

	// Combination of the linear transformation
	Matrix34 operator*(const Matrix34& other) const;

	// Transform of a vector
	Vector3 operator*(const Vector3& vector) const;

	// Assign operator
	float* operator[](int index);

	// Get the Inverse matrix
	Matrix34 Inverse();

	// Set the matrix base on a quaternion and a position
	void SetOrientationAndPosition(const Quaternion& q, const Vector3& p);

	// Transform a position
	Vector3 TransformPosition(const Vector3& vector);

	// Transform a direction by ignoring the translation
	Vector3 TransformDirection(const Vector3& vector);
};

std::ostream& operator<< (std::ostream& os, const Matrix34& matrix34);

Matrix34 operator*(const Matrix34& mat, const float value);
Matrix34 operator*(const float value, const Matrix34& mat);