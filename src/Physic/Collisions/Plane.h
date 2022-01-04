#pragma once
#include "Primitive.h"
#include "Sphere.h"

class Plane : public Primitive
{
private :
    Vector3 normal;
    float offset;
    Vector3 halfSize; // Contient la longueur des 3 demi-côtés


public :

	// Constructors
	Plane();
	Plane(Vector3 normal, float offset, Vector3 center, Vector3 halfSize);

	// Getters & Setters
	Vector3 getNormal() const;
	float getOffset() const;

	void setNormal(Vector3 normal);
	void setOffset(float offset);
	
};

