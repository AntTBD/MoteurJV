#pragma once
#include "Primitive.h"

class Box : public Primitive
{
public:
    Vector3 halfSize; // Contient la longueur des 3 demi-côtés


	// Constructors
	Box();
	Box(Vector3 centre, Vector3 halfsize);

	// Getters & Setters
	Vector3 getHalfSize();
	float getHalfX();
	float getHalfY();
	float getHalfZ();

	void setHalfSize(Vector3 halfSize);
	void setHalfX(float X);
	void setHalfY(float Y);
	void setHalfZ(float Z);

	


};

