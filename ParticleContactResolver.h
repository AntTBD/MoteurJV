#pragma once

#include "ParticleContact.h"

class ParticleContactResolver
{
protected:

	// number of allowed iteration
	unsigned int iteration;

public:

	// take an array of contact
	// iterate on each contact according to their separatingVelocity
	// stop when all contacts are solved or when max iteration is reached
	void resolveContacts(ParticleContact* contactArray, unsigned int numContact, float duration);
};

