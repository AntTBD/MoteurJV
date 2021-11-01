#include "ParticleRod.h"

ParticleRod::ParticleRod(Particle* particle1, Particle* particle2, float length) :
	ParticleLink(particle1, particle2),
	length(length)
{}

ParticleRod::~ParticleRod() {}

unsigned int ParticleRod::addContact(ParticleContact* contact, unsigned int limit)
{
	if (limit > 0)
	{
		float currentLength = this->currentLength();

		if (currentLength > this->length)
		{
			*contact = ParticleContact(this->particle[0], this->particle[1], 1, (currentLength - this->length));
			return 1;
		}
		else if (currentLength < this->length)
		{
			*contact = ParticleContact(this->particle[0], this->particle[1], 1, (this->length - currentLength), true);
			return 1;
		}
		else
		{
			return 0;

		}
	}
	return 0;
}
