#pragma once

#include "Contact.h"
#include <vector>

class ContactResolver
{
protected:

	// number of allowed iteration
	unsigned int maxIteration;

public:
	ContactResolver();

	// take an array of contact
	// iterate on each contact according to their separatingVelocity
	// stop when all contacts are solved or when max iteration is reached
	void resolveContacts(std::vector<Contact*> contactArray, float duration);
};

