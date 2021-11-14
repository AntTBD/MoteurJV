#pragma once

#include "ParticleLink.h"

class ParticleCable :
    public ParticleLink
{
public:

    // a contact will be generated if the distance
    // between particles is larger than maxlength
    float maxLength;

    // float bounciness of the cable
    float restitution;

    ParticleCable(Particle* particle1, Particle* particle2, float maxLength);
    ~ParticleCable();

    // Fill ParticleContact ith information from particles and contact generator
    unsigned int addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const;
};

