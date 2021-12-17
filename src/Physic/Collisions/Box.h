#pragma once
#include "Primitive.h"
class Box
{
private :
	Vector3 centre;
	Vector3 halfSize; // Contient la longueur des 3 demi-côtés

public: 

	// Constructors
	Box();
	Box(Vector3 centre, Vector3 halfsize);

	// Getters & Setters
	Vector3 getCentre();
	Vector3 getHalfSize();
	float getHalfX();
	float getHalfY();
	float getHalfZ();

	void setCentre(Vector3 centre);
	void setHalfSize(Vector3 halfSize);
	void setHalfX(float X);
	void setHalfY(float Y);
	void setHalfZ(float Z);

	// Functions

	float distancePoint(Vector3 point);
	


};

