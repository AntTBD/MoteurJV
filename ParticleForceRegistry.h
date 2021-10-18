#pragma once
#include "ParticleForceGenerator.h"
class ParticleForceRegistry
{
private:
	struct ParticleForceEntry
	{
		Particle* particle;
		ParticleForceGenerator* forceGenerator;
	};

public:
	// 
};

