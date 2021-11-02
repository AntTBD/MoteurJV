#pragma once

#include "ParticleContact.h"
#include <vector>

class ParticleContactGenerator
{
public:
	// Take a pointer to an array of contact and the number of contact left to be generated
	virtual unsigned int addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const = 0;
};

