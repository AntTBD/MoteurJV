#include "Quaternion.h"

Quaternion::Quaternion()
{
	this->w = 0;
	this->i = 0;
	this->j = 0;
	this->k = 0;

}

Quaternion::Quaternion(float w, float i, float j, float k)
{
	this->w = w;
	this->i = i;
	this->j = j;
	this->k = k;
}

Quaternion::Quaternion(float value[4])
{
	memcpy(this->value, value, 4 * sizeof(value[0]));
}

Quaternion::~Quaternion()
{
	delete[] value;
}

float Quaternion::GetW() const
{
	//return this->value[0];
	return this->w;
}

float Quaternion::GetI() const
{
	//return this->value[1];
	return this->i;
}

float Quaternion::GetJ() const
{
	//return this->value[2];
	return this->j;
}

float Quaternion::GetK() const
{
	//return this->value[3];
	return this->k;
}
