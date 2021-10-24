#include "ParticleLink.h"

ParticleLink::ParticleLink(Particle* particle1, Particle* particle2)
{
	this->particle[0] = particle1;
	this->particle[1] = particle2;
}

ParticleLink::~ParticleLink()
{
	this->particle[0] = nullptr;
	this->particle[1] = nullptr;
}

float ParticleLink::currentLength() const
{
	return (this->particle[1]->GetPosition() - this->particle[0]->GetPosition()).Magnitude();
}
