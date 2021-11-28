#include "Rod.h"

Rod::Rod(RigidBody* rigidBody1, RigidBody* rigidBody2, float length) :
	Link(rigidBody1, rigidBody2),
	length(length)
{}

Rod::~Rod() {}

unsigned int Rod::addContact(std::vector<Contact*>* contacts, unsigned int limit) const
{
	if (limit > 0)
	{
		float currentLength = this->currentLength();

		if (currentLength > this->length)
		{
            // Always use zero restitution (no bounciness).
			contacts->push_back(new Contact(this->rigidBody[0], this->rigidBody[1], 0, (currentLength - this->length), true));
			return 1;
		}
		else if (currentLength < this->length)
		{
            // Always use zero restitution (no bounciness).
			contacts->push_back(new Contact(this->rigidBody[0], this->rigidBody[1], 0, (currentLength - this->length)));
			return 1;
		}
		else
		{
			return 0;

		}
	}
	return 0;
}
