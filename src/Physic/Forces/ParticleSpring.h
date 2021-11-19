#pragma once

#include "ParticleForceGenerator.h"

class ParticleSpring : public ParticleForceGenerator
{
private:
    //other anchor
    Particle* m_other;

    // Spring constant
    float m_k;

    float m_restLength;

public:
    ParticleSpring(Particle& other, float k, float restLength);

    ~ParticleSpring();

    // apply Hooke's law based on particles positions
    void UpdateForce(Particle* particle, float duration) override;

};

