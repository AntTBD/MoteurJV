#include "Plane.h"



Plane::Plane()
{
	this->normal = Vector3(1, 1, 1);
	this->offset = 1;
}

Plane::Plane(Vector3 normal, float offset, Vector3 center, Vector3 halfSize)
{
	this->normal = normal;
	this->offset = offset;
    this->center = &center;
    this->halfSize = halfSize;
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