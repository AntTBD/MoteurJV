#include "ParticleLink.h"

ParticleLink::ParticleLink(RigidBody* rigidBody1, RigidBody* rigidBody2)
{
	this->rigidBody[0] = rigidBody1;
	this->rigidBody[1] = rigidBody2;
}

ParticleLink::~ParticleLink()
{
	this->rigidBody[0] = nullptr;
	this->rigidBody[1] = nullptr;
}

float ParticleLink::currentLength() const
{
	return (this->rigidBody[1]->GetPosition() - this->rigidBody[0]->GetPosition()).Magnitude();
}
