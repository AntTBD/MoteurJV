#pragma once

#include "ParticleContactGenerator.h"

class ParticleLink :
    public ParticleContactGenerator
{
protected:
    // Linked particles
    Particle* particle[2];
public:
    ParticleLink(Particle* particle1, Particle* particle2);
    ~ParticleLink();

    // return the length of the link
    float currentLength() const;

    // Take a pointer to an array of contact and the number of contact left to be generated
    unsigned int addContact(ParticleContact* contact, unsigned int limit) = 0;
};

