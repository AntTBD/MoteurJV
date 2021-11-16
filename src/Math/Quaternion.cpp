#include "Quaternion.h"


// Constructors
Quaternion::Quaternion()
{
	this->i = this->j = this->k = 0; // i, j, k
	this->w = 1;  // w
}

Quaternion::Quaternion(float i, float j, float k, float w)
{
	this->i = i;
	this->j = j;
	this->k = k;
	this->w = w;
}

Quaternion::Quaternion(std::vector<float> value){
    this->Set(value);
}

Quaternion::Quaternion(float *value) {
    *this->value = *value;
}


Quaternion::Quaternion(const Vector3& vector, float w)
{
	this->i = vector.GetX();
	this->j = vector.GetY();
	this->k = vector.GetZ();
	this->w = w;

}

Quaternion::Quaternion(const Quaternion &quaternion) {
    *this = quaternion;
}

Quaternion::~Quaternion()
{
}


// Getters

std::vector<float> Quaternion::Get() const {
    return {*this->value};
}

float Quaternion::GetI() const { return this->i; }
float Quaternion::GetJ() const { return this->j; }
float Quaternion::GetK() const { return this->k; }
float Quaternion::GetW() const { return this->w; }


// Setters
void Quaternion::Set(std::vector<float> value)
{
    assert(value.size() == 4  && "Size != 4");
	*this->value = *value.data();
}


void Quaternion::SetI(float i)
{
	this->i = i;
}

void Quaternion::SetJ(float j)
{
	this->j = j;
}

void Quaternion::SetK(float k)
{
	this->k = k;
}

void Quaternion::SetW(float w)
{
	this->w = w;
}


// Functions 

// normalize by multipling the quaternion by the inverse of its magnitude
void Quaternion::Normalized()
{
	float magnitude = float(sqrt(pow(this->i, 2) + pow(this->j, 2) + pow(this->k, 2) + pow(this->w, 2)));
	assert(magnitude != 0 && "Division par 0 ! : Quaternion::Normalized() : magnitude = 0");

	this->i /= magnitude;
	this->j /= magnitude;
	this->k /= magnitude;
	this->w /= magnitude;

}

Quaternion& Quaternion::operator=(const Quaternion &other) {

    this->i = other.GetI();
    this->j = other.GetJ();
    this->k = other.GetK();
    this->w = other.GetW();
    return *this;
}

Quaternion Quaternion::operator+(const Quaternion& other) const
{
	return {
        this->GetI() + other.GetI(),
        this->GetJ() + other.GetJ(),
        this->GetK() + other.GetK(),
        this->GetW() + other.GetW()
    };

	
}

Quaternion& Quaternion::operator+=(const Quaternion& other)
{
	*this = *this + other;
	return  *this;
}

// Quaternion multiplication
Quaternion Quaternion::operator*(const Quaternion& other) const
{
	return {
        this->GetJ() * other.GetK() - this->GetK() * other.GetJ() + this->GetI() * other.GetW() + this->GetW() * other.GetI(),
        this->GetK() * other.GetI() - this->GetI() * other.GetK() + this->GetJ() * other.GetW() + this->GetW() * other.GetJ(),
        this->GetI() * other.GetJ() - this->GetJ() * other.GetI() + this->GetK() * other.GetW() + this->GetW() * other.GetK(),
        this->GetW() * other.GetW() - this->GetI() * other.GetI() - this->GetJ() * other.GetJ() - this->GetK() * other.GetK()
    };
}

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
	*this = *this * other;
	return  *this;
}



Quaternion Quaternion::operator*(float duration) const
{
	return {
        this->GetI() * duration,
        this->GetJ() * duration,
        this->GetK() * duration,
        this->GetW() * duration
    };
}

Quaternion& Quaternion::operator*=(float val) 
{
	*this = *this * val;
	return *this;
}



// Rotate the quaternion by a vector : multiply this by q = (0, dx, dy, dz)
void Quaternion::RotateByVector(const Vector3& vector)
{
	Quaternion vector_bis(vector, 0);

	*this *= vector_bis;
	
}

// Apply the quaternion update by the angular velocity
// this += this->RotateByVector(rotation) * duration
void Quaternion::UpdateByAngularVelocity(const Vector3& rotation, float duration)
{
	Quaternion temp = *this;
	this->RotateByVector(rotation);
	*this *= duration ;
	*this += temp;

}

// Convert Euler Vector3 to Quaternion
Quaternion Quaternion::EulerToQuaternion(const Vector3& euler)
{
	float c1 = cos(euler.GetZ() * 0.5f);
	float c2 = cos(euler.GetY() * 0.5f);
	float c3 = cos(euler.GetX() * 0.5f);
	float s1 = sin(euler.GetZ() * 0.5f);
	float s2 = sin(euler.GetY() * 0.5f);
	float s3 = sin(euler.GetX() * 0.5f);


	return {
        c1 * c2 * s3 - s1 * s2 * c3,
        c1 * s2 * c3 + s1 * c2 * s3,
        s1 * c2 * c3 - c1 * s2 * s3,
        c1 * c2 * c3 + s1 * s2 * s3
    };


}

std::string Quaternion::toString() const
{
	std::stringstream stream;
	stream << *this;
	return stream.str();
}


std::ostream& operator<<(std::ostream& os, const Quaternion& quaternion)
{
	os << "(" << quaternion.GetI() << ", " << quaternion.GetJ() << ", " << quaternion.GetK() << ", " << quaternion.GetW() << ")";
	return os;
}
