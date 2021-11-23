#include "ContactRegistry.h"

ContactRegistry::ContactEntry::ContactEntry(ContactGenerator* contactGenerator, unsigned int limitMax) :
	contactGenerator(contactGenerator),
	limitMax(limitMax)
{}


ContactRegistry::ContactRegistry()
{
	this->contactResolver = new ContactResolver();
}

void ContactRegistry::Add(ContactGenerator* contactGenerator, unsigned int limitMax)
{
	this->m_registry.push_back(ContactRegistry::ContactEntry(contactGenerator, limitMax));
}

void ContactRegistry::UpdateContacts()
{
	nbContacts = 0;
	for (ContactEntry entry : this->m_registry)
	{
		nbContacts += entry.contactGenerator->addContact(&contactList, entry.limitMax);
	}
}

void ContactRegistry::Resolve(float deltaTime)
{
	if (nbContacts > 0) {
		this->contactResolver->resolveContacts(contactList, deltaTime);
	}

	// clear list of contacts
	contactList.clear();
}

void ContactRegistry::Clear()
{
	this->m_registry.clear();
}