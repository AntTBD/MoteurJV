#pragma once

#include "ParticleForceGenerator.h"

class Drag :
    public ParticleForceGenerator
{
private:
    // drag coeffiecents
    float m_k1;
    float m_k2;

public:
    Drag(float k1, float k2);
    ~Drag();

    // apply simplified drag base on object's velocity
    void UpdateForce(RigidBody* rigidBody, float duration) override;
};

