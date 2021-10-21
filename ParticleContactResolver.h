#pragma once

#include "ParticleContact.h"
#include <vector>

class ParticleContactResolver
{
protected:

	// number of allowed iteration
	unsigned int maxIteration;

public:
	// take an array of contact
	// iterate on each contact according to their separatingVelocity
	// stop when all contacts are solved or when max iteration is reached
	void resolveContacts(std::vector<ParticleContact*> contactArray, float duration);
};

