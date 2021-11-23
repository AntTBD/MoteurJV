#pragma once

#include <vector>
#include "ContactGenerator.h"
#include "ParticleContactResolver.h"

class ParticleContactRegistry
{
private:
	struct ParticleContactEntry
	{
		unsigned int limitMax;
		ContactGenerator* contactGenerator;
		ParticleContactEntry(ContactGenerator* forceGenerator, unsigned int limitMax);

	};
	using Registry = std::vector<ParticleContactEntry>;
	Registry m_registry;

	ParticleContactResolver* particleContactResolver;
	std::vector<Contact*> particleContactList;
	unsigned int nbContacts = 0;
public:
	ParticleContactRegistry();
	// ... Registry Accessors
	void Add(ContactGenerator* forceGenerator, unsigned int limitMax);
	void UpdateContacts();
	void Resolve(float deltaTime);
	void Clear();
};

