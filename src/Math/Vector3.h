#pragma once
#include <iostream>
#include <sstream>

class Vector3
{
private:
	float x, y, z;

public:
	// Constructors
	Vector3();
	Vector3(float _x, float _y, float _z);
	Vector3(const Vector3& vector);

	// Operators
	Vector3& operator=(const Vector3& vector);
	Vector3 operator+(const Vector3& vector) const;
	Vector3& operator+=(const Vector3& vector);
	Vector3 operator-(const Vector3& vector) const;
	Vector3& operator-=(const Vector3& vector);
	//Vector3 operator*(float value) const; operator remplacé par operator globale non membre de la classe pour avoir les deux sens
	Vector3& operator*=(float value);
	Vector3 operator/(float value) const;
	Vector3& operator/=(float value);

	// Getters / Setters
	float GetX() const;
	float GetY() const;
	float GetZ() const;
	void SetX(float _x);
	void SetY(float _y);
	void SetZ(float _z);

	// Functions
	
	/// <summary>
	/// xa * xb + ya * yb + za * zb
	/// </summary>
	/// <param name="vector"></param>
	/// <returns></returns>
	float DotProduct(const Vector3& vector) const;

	/// <summary>
	/// (ya * zb - za * yb, <para/>
	/// za * xb - xa * zb, <para/>
	/// xa * yb - ya * xb)
	/// </summary>
	/// <param name="vector"></param>
	/// <returns></returns>
	Vector3 CrossProduct(const Vector3& vector) const;

	/// <summary>
	/// |vector| = sqrt(x² + y² + z²)
	/// </summary>
	/// <returns></returns>
	float Magnitude() const;

	/// <summary>
	/// Squared magnitude is less taxing to calculate and is often enough for what we want to do<para/>
	/// sqrt(x² + y² + z²)² = x² + y² + z²
	/// </summary>
	/// <returns></returns>
	float SquaredMagnitude() const;

	/// <summary>
	/// Make the vector length to 1 <para/>
	/// vec^ = vec / |vec|
	/// </summary>
	/// <returns></returns>
	Vector3& Normalize();

	/// <summary>
	/// Make the vector length to 1 <para/>
	/// vec^ = vec / |vec| <para/>
	/// Withou change original vector
	/// </summary>
	/// <returns></returns>
	Vector3 Normalized() const;

	/// <summary>
	/// Set vector to (0, 0, 0)
	/// </summary>
	/// <returns></returns>
	Vector3& SetZero();


    std::string toString() const;

    // << operator
    friend std::ostream& operator<< (std::ostream& os, const Vector3& vector);

    // * operator dans les 2 sens
    friend Vector3 operator*(const Vector3& vec, float value);
    friend Vector3 operator*(float value, const Vector3& vec);

};
