#include "ParticleRod.h"

ParticleRod::ParticleRod(RigidBody* rigidBody1, RigidBody* rigidBody2, float length) :
	ParticleLink(rigidBody1, rigidBody2),
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
            // Always use zero restitution (no bounciness).
			contacts->push_back(new ParticleContact(this->rigidBody[0], this->rigidBody[1], 0, (currentLength - this->length), true));
			return 1;
		}
		else if (currentLength < this->length)
		{
            // Always use zero restitution (no bounciness).
			contacts->push_back(new ParticleContact(this->rigidBody[0], this->rigidBody[1], 0, (this->length - currentLength)));
			return 1;
		}
		else
		{
			return 0;

		}
	}
	return 0;
}
