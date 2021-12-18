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

/*float Sphere::distance2Spheres(Sphere sphere)
{
	float normalSquare = pow(sphere.getCenter().GetX() - this->center.GetX(), 2) + pow(sphere.getCenter().GetY() - this->center.GetY(), 2) + pow(sphere.getCenter().GetZ() - this->center.GetZ(), 2);
	float sumRadiusSquare = pow(sphere.getRadius() + this->radius, 2);
	return normalSquare - sumRadiusSquare;
}

float Sphere::distancePoint(Vector3 point)
{
	return sqrt(pow(point.GetX() - center.GetX(), 2) + pow(point.GetX() - center.GetX(), 2) + pow(point.GetX() - center.GetX(), 2)) - radius;
}
*/