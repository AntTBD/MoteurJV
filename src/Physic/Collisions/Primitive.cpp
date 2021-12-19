#include "Primitive.h"

Vector3 Primitive::getCenter() const
{
    return *this->center;
}

void Primitive::setCenter(Vector3 center)
{
    this->center = &center;
}

void Primitive::setBody(RigidBody *body) {
    this->body = body;
    this->center = &this->body->position;
}
