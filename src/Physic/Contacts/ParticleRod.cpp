#include "ParticleRod.h"

ParticleRod::ParticleRod(Particle* particle1, Particle* particle2, float length) :
	ParticleLink(particle1, particle2),
	length(length)
{}

ParticleRod::~ParticleRod() {}

unsigned int ParticleRod::addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const
{
	if (limit > 0)
	{
		float currentLength = this->currentLength();

		if (currentLength > this->length)
		{
			contacts->push_back(new ParticleContact(this->particle[0], this->particle[1], 1, (currentLength - this->length), true));
			return 1;
		}
		else if (currentLength < this->length)
		{
			contacts->push_back(new ParticleContact(this->particle[0], this->particle[1], 1, (this->length - currentLength)));
			return 1;
		}
		else
		{
			return 0;

		}
	}
	return 0;
}
