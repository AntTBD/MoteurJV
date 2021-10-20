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
	using Registry = std::vector<ParticleForceEntry>;
	Registry  m_registry;
public:
	// ... Registry Accessors
	void Add(Particle* particle, ParticleForceGenerator* forceGenerator);
	void UpdateForce(float duration);
	void Clear();
};

