#include "ParticleCable.h"


ParticleCable::ParticleCable(Particle* particle1, Particle* particle2, float maxLength) :
	ParticleLink(particle1, particle2), 
	maxLength(maxLength), restitution(1.0f)
{}

ParticleCable::~ParticleCable() {}

unsigned int ParticleCable::addContact(ParticleContact* contact, unsigned int limit)
{
	if (limit > 0)
	{
		if (this->currentLength() >= this->maxLength)
		{
			*contact = ParticleContact(this->particle[0], this->particle[1], this->restitution, (this->currentLength() - this->maxLength));
			return 1;
		}
	}
	return 0;
}
