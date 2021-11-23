#include "Cable.h"


Cable::Cable(RigidBody* rigidBody1, RigidBody* rigidBody2, float maxLength) :
	Link(rigidBody1, rigidBody2),
	maxLength(maxLength), restitution(1.0f)
{}

Cable::~Cable() {}

unsigned int Cable::addContact(std::vector<Contact*>* contacts, unsigned int limit) const
{
	if (limit > 0)
	{
		if (this->currentLength() >= this->maxLength)
		{
			contacts->push_back(new Contact(this->rigidBody[0], this->rigidBody[1], this->restitution, (this->currentLength() - this->maxLength), true));
			return 1;
		}
	}
	return 0;
}
