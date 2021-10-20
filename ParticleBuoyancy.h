#pragma once

#include "ParticleForceGenerator.h"

class ParticleBuoyancy : public ParticleForceGenerator
{
private:
    // particule properties
    float m_maxDepth;
    float m_volume;

    // effect properties
    float m_waterHeight;
    float m_liquidDensity;

public:
    ParticleBuoyancy(double maxDepth, double volume, double waterHeight, double liquidDensity);
    ~ParticleBuoyancy();

    // apply Buoyancy based on particle position
    void UpdateForce(Particle* particle, float duration);
};

