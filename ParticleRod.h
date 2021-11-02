#pragma once

#include "ParticleLink.h"

class ParticleRod :
    public ParticleLink
{
public:

    // a contact will be generated if the distance
    // between particles is not equal to the length
    float length;

    ParticleRod(Particle* particle1, Particle* particle2, float length);
    ~ParticleRod();

    // Fill ParticleContact with information form particles and contact generator.
    // Contact is different wether the disitance is shaorter or greater than the length
    unsigned int addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const;
};

