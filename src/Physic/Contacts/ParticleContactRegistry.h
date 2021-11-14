#pragma once

#include <vector>
#include "ParticleContactGenerator.h"
#include "ParticleContactResolver.h"

class ParticleContactRegistry
{
private:
	struct ParticleContactEntry
	{
		unsigned int limitMax;
		ParticleContactGenerator* contactGenerator;
		ParticleContactEntry(ParticleContactGenerator* forceGenerator, unsigned int limitMax);

	};
	using Registry = std::vector<ParticleContactEntry>;
	Registry m_registry;

	ParticleContactResolver* particleContactResolver;
	std::vector<ParticleContact*> particleContactList;
	unsigned int nbContacts = 0;
public:
	ParticleContactRegistry();
	// ... Registry Accessors
	void Add(ParticleContactGenerator* forceGenerator, unsigned int limitMax);
	void UpdateContacts();
	void Resolve(float deltaTime);
	void Clear();
};

