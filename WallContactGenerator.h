#pragma once

#include "ParticleContactGenerator.h"

class WallContactGenerator :
    public ParticleContactGenerator
{
private:
    Particle* particle;
    Particle* wall;
public: 
    WallContactGenerator(Particle* particle);
    ~WallContactGenerator();
    

    // Fill ParticleContact with information form particles and contact generator.
    // Contact is different wether the disitance is shaorter or greater than the length
    unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

