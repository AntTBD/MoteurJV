#include "Sphere.h"

Sphere::Sphere()
{
	this->center = Vector3();
	this->radius = 1;
}

Sphere::Sphere(Vector3 center, float radius)
{
	this->center = center;
	this->radius = radius;
}

float Sphere::getRadius()
{
	return this->radius;
}


void Sphere::setRadius(float radius)
{
	this->radius = radius;
}