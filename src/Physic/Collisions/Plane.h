#pragma once
#include "Primitive.h"
#include "Sphere.h"

class Plane : public Primitive
{
private :
		Vector3 normal;
		float offset; 


public :

	// Constructors
	Plane();
	Plane(Vector3 normal, float offset);

	// Getters & Setters
	Vector3 getNormal();
	float getOffset();

	void setNormal(Vector3 normal);
	void setOffset(float offset);




	//float distancePoint(Vector3 point);
	//float distanceSpherePlan(Sphere sphere);
	
};

