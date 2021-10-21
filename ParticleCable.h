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

    // Fill ParticleContact ith information from particles and contact generator
    unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

