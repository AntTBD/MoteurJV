#pragma once
#include "ParticleForceGenerator.h"

#include <vector>

class ParticleForceRegistry
{
private:
	struct ParticleForceEntry
	{
		Particle* particle;
		ParticleForceGenerator* forceGenerator;

		ParticleForceEntry(Particle* particle, ParticleForceGenerator* forceGenerator);
	};

	std::vector<ParticleForceEntry> registry;
public:
	// ... Registry Accessors
	void Add(Particle* particle, ParticleForceGenerator* forceGenerator);
	void UpdateForce(float duration);
	void Clear();
};

