#include "Plane.h"



Plane::Plane()
{
	this->normal = Vector3(1, 1, 1);
	this->offset = 1;
}

Plane::Plane(Vector3 normal, float offset)
{
	this->normal = normal;
	this->offset = offset;
}

Vector3 Plane::getNormal() const
{
	return this->normal;
}

float Plane::getOffset() const
{
	return this->offset;
}

void Plane::setNormal(Vector3 normal)
{
	this->normal = normal;
}

void Plane::setOffset(float offset)
{
	this->offset = offset;
}