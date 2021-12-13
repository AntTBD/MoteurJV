#pragma once
#include "Primitive.h"
class Sphere : public Primitive
{
private :
	Vector3 centre;
	float radius;
		

public :
	float distancePoint(Vector3 point);
	
		 


};

