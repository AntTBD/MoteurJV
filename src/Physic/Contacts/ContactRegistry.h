#pragma once

#include <vector>
#include "ContactGenerator.h"
#include "ContactResolver.h"

class ContactRegistry
{
private:
	struct ContactEntry
	{
		unsigned int limitMax;
		ContactGenerator* contactGenerator;
		ContactEntry(ContactGenerator* contactGenerator, unsigned int limitMax);

	};
	using Registry = std::vector<ContactEntry>;
	Registry m_registry;

	ContactResolver* contactResolver;
	std::vector<Contact*> contactList;
	unsigned int nbContacts = 0;
public:
	ContactRegistry();
	// ... Registry Accessors
	void Add(ContactGenerator* contactGenerator, unsigned int limitMax);
	void UpdateContacts();
	void Resolve(float deltaTime);
	void Clear();

    void SetContactList(std::vector<Contact*> list);
};

