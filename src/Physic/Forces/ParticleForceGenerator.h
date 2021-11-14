#pragma once

#include "src/Physics/Particle.h"

class ParticleForceGenerator
{
public:
	virtual void UpdateForce(Particle* particle, float duration) = 0;
};

