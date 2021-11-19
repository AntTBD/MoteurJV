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
    ParticleBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity = 1000.0f);
    ~ParticleBuoyancy();

    // apply Buoyancy based on particle position
    void UpdateForce(RigidBody* rigidBody, float duration) override;
};

