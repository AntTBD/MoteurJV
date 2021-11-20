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
    return { *this->value };
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


// Operators
Quaternion& Quaternion::operator=(const Quaternion& other) {

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



Quaternion Quaternion::operator*(float val) const
{
	return {
		this->GetI() * val,
		this->GetJ() * val,
		this->GetK() * val,
		this->GetW() * val
	};
}

Quaternion& Quaternion::operator*=(float val)
{
	*this = *this * val;
	return *this;
}


// Functions 

// normalize by multipling the quaternion by the inverse of its magnitude
void Quaternion::Normalize()
{
	float magnitude = float(sqrt(pow(this->i, 2.f) + pow(this->j, 2.f) + pow(this->k, 2.f) + pow(this->w, 2.f)));
	//assert(magnitude != 0 && "Division par 0 ! : Quaternion::Normalized() : magnitude = 0");

    if(magnitude != 0) {
        this->i /= magnitude;
        this->j /= magnitude;
        this->k /= magnitude;
        this->w /= magnitude;
    }
}
Quaternion Quaternion::Normalized() const
{
	float magnitude = float(sqrt(pow(this->i, 2.f) + pow(this->j, 2.f) + pow(this->k, 2.f) + pow(this->w, 2.f)));
	//assert(magnitude != 0 && "Division par 0 ! : Quaternion::Normalized() : magnitude = 0");

    if(magnitude == 0) return *this;
	return { 
		this->i / magnitude,
		this->j / magnitude,
		this->k / magnitude,
		this->w / magnitude 
	};

}

Quaternion Quaternion::Conjugate() const
{
	return {-this->i, -this->j, -this->k, this->w };
}





// Rotate the quaternion by a vector : multiply this by q = (0, dx, dy, dz)
void Quaternion::RotateByVector(const Vector3& vector)
{
	Quaternion vector_bis(vector, 0);
	this->Normalize();
	vector_bis.Normalize();

	*this *= vector_bis * this->Conjugate();
	
}
// Rotate the quaternion by a vector : multiply this by q = (0, dx, dy, dz)
Quaternion Quaternion::RotatedByVector(const Vector3& vector) const
{
	Quaternion vector_bis(vector, 0);

	return this->Normalized() * vector_bis * this->Normalized().Conjugate();

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

Quaternion Quaternion::EulerInDegreesToQuaternion(const Vector3 &euler) {
    return EulerToQuaternion(euler * M_PI / 180.f);
}

// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
Vector3 Quaternion::ToEuler() const {
    Vector3 angles;

    // roll (x-axis rotation)
    float sinr_cosp = 2.f * (this->w * this->i + this->j * this->k);
    float cosr_cosp = 1.f - 2.f * (this->i * this->i + this->j * this->j);
    angles.SetX(std::atan2f(sinr_cosp, cosr_cosp));

    // pitch (y-axis rotation)
    float sinp = 2.f * (this->w * this->j - this->k * this->i);
    if (std::abs(sinp) >= 1)
        angles.SetY(std::copysignf(M_PI / 2.f, sinp)); // use 90 degrees if out of range
    else
        angles.SetY(std::asinf(sinp));

    // yaw (z-axis rotation)
    float siny_cosp = 2.f * (this->w * this->k + this->i * this->j);
    float cosy_cosp = 1.f - 2.f * (this->j * this->j + this->k * this->k);
    angles.SetZ(std::atan2f(siny_cosp, cosy_cosp));

    return angles * 180.f / M_PI;
}

Vector3 Quaternion::ToEulerInDegrees() const {

    return this->ToEuler() * 180.f / M_PI;
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

Quaternion operator*(float value, const Quaternion &quaternion) {
	return quaternion * value;
}
