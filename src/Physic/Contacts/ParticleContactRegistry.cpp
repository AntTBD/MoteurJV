#include "ParticleContactRegistry.h"

ParticleContactRegistry::ParticleContactEntry::ParticleContactEntry(ContactGenerator* contactGenerator, unsigned int limitMax) :
	contactGenerator(contactGenerator),
	limitMax(limitMax)
{}


ParticleContactRegistry::ParticleContactRegistry()
{
	this->particleContactResolver = new ParticleContactResolver();
}

void ParticleContactRegistry::Add(ContactGenerator* contactGenerator, unsigned int limitMax)
{
	this->m_registry.push_back(ParticleContactRegistry::ParticleContactEntry(contactGenerator, limitMax));
}

void ParticleContactRegistry::UpdateContacts()
{
	nbContacts = 0;
	for (ParticleContactEntry entry : this->m_registry)
	{
		nbContacts += entry.contactGenerator->addContact(&particleContactList, entry.limitMax);
	}
}

void ParticleContactRegistry::Resolve(float deltaTime)
{
	if (nbContacts > 0) {
		this->particleContactResolver->resolveContacts(particleContactList, deltaTime);
	}

	// clear list of contacts
	particleContactList.clear();
}

void ParticleContactRegistry::Clear()
{
	this->m_registry.clear();
}