#include "Box.h"


// Constuctors
Box::Box()
{
	this->centre = Vector3();
	this->halfSize = Vector3(1, 1, 1);
}

Box::Box(Vector3 centre, Vector3 halfsize)
{
	this->centre = centre;
	this->halfSize = halfSize;
}

// Getters
Vector3 Box::getCentre()
{
	return this->centre;
}

Vector3 Box::getHalfSize()
{
	return this->halfSize;
}

float Box::getHalfX()
{
	return this->halfSize.GetX();
}

float Box::getHalfY()
{
	return this->halfSize.GetY();
}

float Box::getHalfZ()
{
	return this->halfSize.GetZ();
}

// Setters
void Box::setCentre(Vector3 centre)
{
	this->centre = centre;
}

void Box::setHalfSize(Vector3 halfSize)
{
	this->halfSize = halfSize;
}

void Box::setHalfX(float X)
{
	this->halfSize.SetX(X);
}

void Box::setHalfY(float Y)
{
	this->halfSize.SetY(Y);
}

void Box::setHalfZ(float Z)
{
	this->halfSize.SetZ(Z);
}


// Functions 
float Box::distancePoint(Vector3 point)
{
	return 0.0f;
}
