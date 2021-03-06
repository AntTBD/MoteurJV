#include "Vector3.h"

// Constructors
Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
}

Vector3::Vector3(const Vector3& vector)
{
	this->x = vector.GetX();
	this->y = vector.GetY();
	this->z = vector.GetZ();
}

// Operators overload
Vector3& Vector3::operator=(const Vector3& vector)
{
	this->x = vector.GetX();
	this->y = vector.GetY();
	this->z = vector.GetZ();
	return *this;
}

Vector3 Vector3::operator+(const Vector3& vector) const
{
	return Vector3(this->x + vector.GetX(), this->y + vector.GetY(), this->z + vector.GetZ());
}

Vector3& Vector3::operator+=(const Vector3& vector)
{
	this->x += vector.GetX();
	this->y += vector.GetY();
	this->z += vector.GetZ();
	return *this;
}

Vector3 Vector3::operator-(const Vector3& vector) const
{
	return Vector3(this->x - vector.GetX(), this->y - vector.GetY(), this->z - vector.GetZ());
}

Vector3& Vector3::operator-=(const Vector3& vector)
{
	this->x -= vector.GetX();
	this->y -= vector.GetY();
	this->z -= vector.GetZ();
	return *this;
}

/*Vector3 Vector3::operator*(float value) const
{
	return Vector3(this->x * value, this->y * value, this->z * value);
}*/

Vector3 Vector3::operator*(const Vector3 &vector) const
{
    return {this->x * vector.GetX(),
    this->y * vector.GetY(),
    this->z * vector.GetZ()
    };
}

Vector3& Vector3::operator*=(const Vector3 &vector)
{
    this->x *= vector.GetX();
    this->y *= vector.GetY();
    this->z *= vector.GetZ();
    return *this;
}

Vector3& Vector3::operator*=(float value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	return *this;
}

Vector3 Vector3::operator/(float value) const
{
	assert(value != 0 && "Vector3: Division by 0");
	return Vector3(this->x / value, this->y / value, this->z / value);
}

Vector3& Vector3::operator/=(float value)
{
	assert(value != 0 && "Vector3: Division by 0");
	this->x /= value;
	this->y /= value;
	this->z /= value;
	return *this;
}

std::string Vector3::toString() const
{
    std::stringstream stream;
    stream << *this;
    return stream.str();
}

std::ostream& operator<<(std::ostream& os, const Vector3& vector)
{
	os << "(" << vector.GetX() << "," << vector.GetY() << "," << vector.GetZ() << ")";
	return os;
}

Vector3 operator*(const Vector3& vec, float value)
{
	return {vec.GetX() * value, vec.GetY() * value, vec.GetZ() * value};
}

Vector3 operator*(float value, const Vector3& vec)
{
	return vec * value;
}

bool Vector3::operator==(const Vector3 &vector) const {
    return this->GetX() == vector.GetX() && this->GetY() == vector.GetY() && this->GetZ() == vector.GetZ();
}

bool Vector3::operator!=(const Vector3 &vector) const {
    return this->GetX() != vector.GetX() || this->GetY() != vector.GetY() || this->GetZ() != vector.GetZ();
}

// Getters and Setters
float Vector3::GetX() const
{
	return this->x;
}

float Vector3::GetY() const
{
	return this->y;
}

float Vector3::GetZ() const
{
	return this->z;
}

void Vector3::SetX(float _x)
{
	this->x = _x;
}

void Vector3::SetY(float _y)
{
	this->y = _y;
}

void Vector3::SetZ(float _z)
{
	this->z = _z;
}

// Functions
float Vector3::DotProduct(const Vector3& vector) const
{
	return this->x * vector.GetX() + this->y * vector.GetY() + this->z * vector.GetZ();
}

Vector3 Vector3::CrossProduct(const Vector3& vector) const
{
	return Vector3(this->y * vector.GetZ() - this->z * vector.GetY(), this->z * vector.GetX() - this->x * vector.GetZ(), this->x * vector.GetY() - this->y * vector.GetX());
}

float Vector3::Magnitude() const
{
	return float(sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
}

float Vector3::SquaredMagnitude() const // Squared magnitude is less taxing to calculate and is often enough for what we want to do
{
	return float(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

Vector3& Vector3::Normalize() // Make the vector length to 1
{
	float length = this->Magnitude();
	assert(length != 0 && "Division par 0 ! : Vector3::Normalize() : Magnitude = 0");
	*this /= length;
	return *this;
}

Vector3 Vector3::Normalized() const // Make the vector length to 1 - without change original vector
{
	float length = this->Magnitude();
    assert(length != 0 && "Division par 0 ! : Vector3::Normalized() : Magnitude = 0");
	return *this / length;
}

Vector3& Vector3::SetZero() // Set vector to (0, 0, 0)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	return *this;
}

float Vector3::GetMaxValue() const {
	float length1 = std::max(this->x, std::max(this->y, this->z));
	float length2;
	if (length1 == this->x) length2 = std::max(this->y, this->z);
	else if (length1 == this->y) length2 = std::max(this->x, this->z);
	else if (length1 == this->z) length2 = std::max(this->x, this->y);

	return (sqrt((length1 * length1) + (length2 * length2)));
	

    return std::max({this->x, this->y, this->z});;


}

float Vector3::GetMinValue() const {
    return std::min({this->x, this->y, this->z});;
}
