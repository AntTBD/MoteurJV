#include "Sphere.h"

Sphere::Sphere()
{
	this->centre = Vector3();
	this->radius = 1;
}

Sphere::Sphere(Vector3 centre, float radius)
{
	this->centre = centre;
	this->radius = radius;
}

Vector3 Sphere::getCentre()
{
	return this->centre;
}

float Sphere::getRadius()
{
	return this->radius;
}

void Sphere::setCentre(Vector3 centre)
{
	this->centre = centre;
}

void Sphere::setRadius(float radius)
{
	this->radius = radius;
}

float Sphere::distance2Spheres(Sphere sphere)
{
	float normalSquare = pow(sphere.getCentre().GetX() - this->centre.GetX(), 2) + pow(sphere.getCentre().GetY() - this->centre.GetY(), 2) + pow(sphere.getCentre().GetZ() - this->centre.GetZ(), 2);
	float sumRadiusSquare = pow(sphere.getRadius() + this->radius, 2);
	return normalSquare - sumRadiusSquare;
}

float Sphere::distancePoint(Vector3 point)
{
	return sqrt(pow(point.GetX() - centre.GetX(), 2) + pow(point.GetX() - centre.GetX(), 2) + pow(point.GetX() - centre.GetX(), 2)) - radius;
}
