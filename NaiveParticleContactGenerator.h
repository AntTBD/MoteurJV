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
    std::vector<Particle*>* particles;

    NaiveParticleContactGenerator(std::vector<Particle*>* particles, float radius);
    ~NaiveParticleContactGenerator();

    // do not use
    unsigned int addContact(ParticleContact* contact, unsigned int limit) {
        return -1;
    }

    // iterate throught every pair of particles to check their penetration
    unsigned int addContact(std::vector<ParticleContact*>* contacts, unsigned int limit);
};

