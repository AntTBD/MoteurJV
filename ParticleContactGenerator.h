#pragma once

#include "ParticleContact.h"

class ParticleContactGenerator
{
public:
	// Take a pointer to an array of contact and the number of contact left to be generated
	virtual unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;
};

