#pragma once

#include "ForceGenerator.h"

class ParticleSpring : public ForceGenerator
{
private:
    //other anchor
    RigidBody* m_other;

    // Spring constant
    float m_k;

    float m_restLength;

public:
    ParticleSpring(RigidBody& other, float k, float restLength);

    ~ParticleSpring();

    // apply Hooke's law based on particles positions
    void UpdateForce(RigidBody* rigidBody, float duration) override;

};

