#pragma once

#include "ParticleContactGenerator.h"
#include <vector>

class NaiveParticleContactGenerator :
    public ParticleContactGenerator
{
public:
    // Particle radius
    float radius;

    // particles that could collide together
    std::vector<Particle*> particles;

    // iterate throught every pair of particles to check their penetration
    unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

