#pragma once

#include "ParticleContactGenerator.h"
#include <vector>

class NaiveContactGenerator :
    public ParticleContactGenerator
{
public:
    // Particle radius
    float radius;

    // particles that could collide together
    std::vector<RigidBody*>* rigidBodies;

    NaiveContactGenerator(std::vector<RigidBody*>* RigidBodies, float radius = 10);
    ~NaiveContactGenerator();

    // iterate throught every pair of particles to check their penetration
    unsigned int addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const override;
};

