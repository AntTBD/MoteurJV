#include "Primitive.h"

Vector3 Primitive::getCenter() const
{
    return this->center;
}

void Primitive::setCenter(Vector3 center)
{
    this->center = center;
}

float Primitive::distancePoint(Vector3 point)
{
	return 0.0f;
}
