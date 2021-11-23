#pragma once

#include "ContactGenerator.h"

class Link :
    public ContactGenerator
{
protected:
    // Linked objects
    RigidBody* rigidBody[2];
public:
    Link(RigidBody* rigidBody1, RigidBody* rigidBody2);
    ~Link();

    // return the length of the link
    float currentLength() const;

    // Take a pointer to an array of contact and the number of contact left to be generated
    unsigned int addContact(std::vector<Contact*>* contacts, unsigned int limit) const override = 0;
};

