#include "ParticleCable.h"


ParticleCable::ParticleCable(Particle* particle1, Particle* particle2, float maxLength) :
	ParticleLink(particle1, particle2), 
	maxLength(maxLength), restitution(0.0f)
{}

ParticleCable::~ParticleCable() {}

unsigned int ParticleCable::addContact(ParticleContact* contact, unsigned int limit) const
{
	if (limit > 0)
	{
		if (this->currentLength() >= this->maxLength)
		{
			contact = new ParticleContact(*this->particle[0], *this->particle[1], this->restitution, (this->currentLength() - this->maxLength));
			return 1;
		}
	}
	return 0;
}
