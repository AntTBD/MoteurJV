#include "Link.h"

Link::Link(RigidBody* rigidBody1, RigidBody* rigidBody2)
{
	this->rigidBody[0] = rigidBody1;
	this->rigidBody[1] = rigidBody2;
}

Link::~Link()
{
	this->rigidBody[0] = nullptr;
	this->rigidBody[1] = nullptr;
}

float Link::currentLength() const
{
	return (this->rigidBody[0]->GetPosition() - this->rigidBody[1]->GetPosition()).Magnitude();
}
