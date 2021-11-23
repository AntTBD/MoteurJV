#pragma once

#include "Contact.h"
#include <vector>

class ContactGenerator
{
public:
	// Take a pointer to an array of contact and the number of contact left to be generated
	virtual unsigned int addContact(std::vector<Contact*>* contacts, unsigned int limit) const = 0;
};

