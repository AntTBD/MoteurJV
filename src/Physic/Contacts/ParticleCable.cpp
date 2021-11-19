#include "ParticleCable.h"


ParticleCable::ParticleCable(RigidBody* rigidBody1, RigidBody* rigidBody2, float maxLength) :
	ParticleLink(rigidBody1, rigidBody2),
	maxLength(maxLength), restitution(1.0f)
{}

ParticleCable::~ParticleCable() {}

unsigned int ParticleCable::addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const
{
	if (limit > 0)
	{
		if (this->currentLength() >= this->maxLength)
		{
			contacts->push_back(new ParticleContact(this->rigidBody[0], this->rigidBody[1], this->restitution, (this->currentLength() - this->maxLength), true));
			return 1;
		}
	}
	return 0;
}
