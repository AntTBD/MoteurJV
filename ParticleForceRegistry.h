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
	};

	using Registry = std::vector<ParticleForceGenerator>;
	Registry m_registry;

public:
	// ... Registry Accessors
	void UpdateForce(float duration);
};

