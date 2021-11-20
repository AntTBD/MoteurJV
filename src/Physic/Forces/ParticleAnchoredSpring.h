#pragma once

#include "ParticleForceGenerator.h"

class ParticleAnchoredSpring : public ParticleForceGenerator
{
private:
    //other anchor
    Vector3* m_anchor;

    // Spring constant
    float m_k;

    float m_restLenght;

public:
    ParticleAnchoredSpring(Vector3& anchor, float k, float restLenght);

    ~ParticleAnchoredSpring();

    // apply Hooke's law based on particles positions
    void UpdateForce(RigidBody* rigidBody, float duration) override;

};

