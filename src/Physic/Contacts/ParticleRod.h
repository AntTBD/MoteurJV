#pragma once

#include "Link.h"

class ParticleRod :
    public Link
{
public:

    // a contact will be generated if the distance
    // between particles is not equal to the length
    float length;

    ParticleRod(RigidBody* rigidBody1, RigidBody* rigidBody2, float length);
    ~ParticleRod();

    // Fill ParticleContact with information form particles and contact generator.
    // Contact is different wether the disitance is shaorter or greater than the length
    unsigned int addContact(std::vector<Contact*>* contacts, unsigned int limit) const override;
};

