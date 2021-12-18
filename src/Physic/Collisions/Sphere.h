#pragma once
#include "Primitive.h"

class Sphere : public Primitive
{
public :
	float radius;

	// Constructors

	Sphere();
	Sphere(Vector3 center, float radius);



	// Getters & Setters
	float getRadius();

	void setRadius(float radius);
};

