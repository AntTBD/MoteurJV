#pragma once

#include "Link.h"

class Rod :
    public Link
{
public:

    // a contact will be generated if the distance
    // between objects is not equal to the length
    float length;

    Rod(RigidBody* rigidBody1, RigidBody* rigidBody2, float length);
    ~Rod();

    // Fill Contact with information form objects and contact generator.
    // Contact is different wether the distance is shorter or greater than the length
    unsigned int addContact(std::vector<Contact*>* contacts, unsigned int limit) const override;
};

