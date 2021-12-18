#pragma once
#include "Primitive.h"
class Sphere : public Primitive
{
private :
	float radius;
		

public :

	// Constructors

	Sphere();
	Sphere(Vector3 center, float radius);



	// Getters & Setters
	Vector3 getCentre();
	float getRadius();

	void setCentre(Vector3 centre);
	void setRadius(float radius);









	float distance2Spheres(Sphere sphere);

	float distancePoint(Vector3 point);
	
		 


};

