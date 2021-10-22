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

		if (currentLength == this->length) return 0;

		else if (currentLength > this->length)
		{
			*contact = ParticleContact(this->particle[0], this->particle[1], 0, (this->currentLength() - this->length));
			return 1;
		}
		else if (currentLength < this->length)
		{
			*contact = ParticleContact(this->particle[1], this->particle[0], 0, (this->length - this->currentLength()));
			return 1;
		}
	}
	return 0;
}
