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

Vector3 Plane::getNormal()
{
	return this->normal;
}

float Plane::getOffset()
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

float Plane::distancePoint(Vector3 point)
{
	return normal.Normalize().DotProduct(point) - offset;
}

float Plane::distanceSpherePlan(Sphere sphere)
{
	return normal.Normalize().DotProduct(sphere.getCentre()) - offset;

	return 0.0f;
}
