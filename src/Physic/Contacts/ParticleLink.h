#pragma once

#include "ContactGenerator.h"

class ParticleLink :
    public ContactGenerator
{
protected:
    // Linked particles
    RigidBody* rigidBody[2];
public:
    ParticleLink(RigidBody* rigidBody1, RigidBody* rigidBody2);
    ~ParticleLink();

    // return the length of the link
    float currentLength() const;

    // Take a pointer to an array of contact and the number of contact left to be generated
    unsigned int addContact(std::vector<Contact*>* contacts, unsigned int limit) const override = 0;
};

