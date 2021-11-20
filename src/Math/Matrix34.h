#pragma once

// pour eviter les problèmes d'includes recursifs
class Matrix33;
class Matrix34;

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix33.h"
#include <vector>
#include <assert.h>

class Matrix34
{
private:
	// value of the Matrix 3X4
	std::vector<float> values;

public:
	Matrix34();
	Matrix34(std::vector<float> value);
	Matrix34(const Matrix34& matrix34);
	Matrix34(const Matrix33& matrix33, const Vector3& vec);
	~Matrix34() = default;

	std::vector<float> Get() const;
	float Get(int index) const;
	Matrix33 GetMatrix33() const;
	Vector3 GetVector() const;

    // return transform matrix to be used with opengl (with transpose)
    std::vector<float> GetMatrix44ForGL() const;

	void Set(std::vector<float> value);

	Matrix34& operator=(const Matrix34& other);

	// Combination of the linear transformation
	Matrix34 operator*(const Matrix34& other) const;

	// Transform of a vector
	Vector3 operator*(const Vector3& vector) const;

	// Assign operator
	std::vector<float> operator[](int index);
    std::vector<float> operator[](int index) const;

	// Get the Inverse matrix
	Matrix34 Inverse() const;

	// Set the matrix base on a quaternion and a position
	void SetOrientationAndPosition(const Quaternion& q, const Vector3& p);

	// Transform a position
	Vector3 TransformPosition(const Vector3& vector) const;
    Vector3 TransformInversePosition(const Vector3& vector) const;

	// Transform a direction by ignoring the translation
	Vector3 TransformDirection(const Vector3& vector) const;
    Vector3 TransformInverseDirection(const Vector3& vector) const;


    std::string toString() const;
    friend std::ostream& operator<< (std::ostream& os, const Matrix34& matrix34);

    friend Matrix34 operator*(const Matrix34& mat, float value);
    friend Matrix34 operator*(float value, const Matrix34& mat);
};
