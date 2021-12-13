#pragma once
#include "Primitive.h"
class Box
{
private :
	Vector3 centre;
	Vector3 halfSize; // Contient la longueur des 3 demi-côtés

public: 

	float distancePoint(Vector3 point);



};

