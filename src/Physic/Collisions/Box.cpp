#include "Box.h"


// Constuctors
Box::Box()
{
	this->center = Vector3();
	this->halfSize = Vector3(1, 1, 1);
}

Box::Box(Vector3 center, Vector3 halfsize)
{
	this->center = center;
	this->halfSize = halfSize;
}

// Getters

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
