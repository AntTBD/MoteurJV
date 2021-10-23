#pragma once

#include "ParticleContactGenerator.h"
#include <vector>

class WallContactGenerator :
    public ParticleContactGenerator
{
private:
    // particles that could collide the wall
    std::vector<Particle*>* particles;

    float positionY;
public: 
    WallContactGenerator(std::vector<Particle*>* particles, float positionY = 0);
    ~WallContactGenerator();
    
    // do not use
    unsigned int addContact(ParticleContact* contact, unsigned int limit) {
        return -1;
    }

    // Fill ParticleContact with information form particles and contact generator.
    // Contact is different wether the disitance is shaorter or greater than the length
    unsigned int addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const;
};

