#include "Primitive.h"

Vector3 Primitive::getCenter() const
{
    return this->center;
}

void Primitive::setCenter(Vector3 center)
{
    this->center = center;
}