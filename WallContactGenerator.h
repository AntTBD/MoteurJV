#pragma once

#include "ParticleContactGenerator.h"

class WallContactGenerator :
    public ParticleContactGenerator
{
private:
    Particle* particle;
    Particle* wall;

    float positionY;
public: 
    WallContactGenerator(Particle* particle, float positionY = 0);
    ~WallContactGenerator();
    

    // Fill ParticleContact with information form particles and contact generator.
    // Contact is different wether the disitance is shaorter or greater than the length
    unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

