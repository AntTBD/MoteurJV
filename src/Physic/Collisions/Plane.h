#pragma once
#include "Primitive.h"
class Plane : public Primitive
{
private :
		Vector3 normal;
		float offset; 


public :

	float distancePoint(Vector3 point);
	
};

