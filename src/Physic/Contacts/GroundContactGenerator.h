#pragma once

#include "ParticleContactGenerator.h"
#include <vector>

class GroundContactGenerator :
    public ParticleContactGenerator
{
private:
    // particles that could collide the wall
    std::vector<Particle*>* particles;

    float positionY;
public: 
    GroundContactGenerator(std::vector<Particle*>* particles, float positionY = 0);
    ~GroundContactGenerator();

    // Fill ParticleContact with information form particles and contact generator.
    // Contact is different wether the disitance is shaorter or greater than the length
    unsigned int addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const override;
};

