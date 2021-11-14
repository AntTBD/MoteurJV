#include "ParticleCable.h"


ParticleCable::ParticleCable(Particle* particle1, Particle* particle2, float maxLength) :
	ParticleLink(particle1, particle2), 
	maxLength(maxLength), restitution(1.0f)
{}

ParticleCable::~ParticleCable() {}

unsigned int ParticleCable::addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const
{
	if (limit > 0)
	{
		if (this->currentLength() >= this->maxLength)
		{
			contacts->push_back(new ParticleContact(this->particle[0], this->particle[1], this->restitution, (this->currentLength() - this->maxLength), true));
			return 1;
		}
	}
	return 0;
}
