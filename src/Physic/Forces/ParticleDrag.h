#pragma once

#include "ParticleForceGenerator.h"

class ParticleDrag :
    public ParticleForceGenerator
{
private:
    // drag coeffiecents
    float m_k1;
    float m_k2;

public:
    ParticleDrag(float k1, float k2);
    ~ParticleDrag();

    // apply simplified drag base on particle's velocity
    void UpdateForce(Particle* particle, float duration) override;
};

