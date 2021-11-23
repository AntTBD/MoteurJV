#pragma once

#include "ForceGenerator.h"

class Spring : public ForceGenerator
{
private:
    //other anchor
    RigidBody* m_other;

    // Spring constant
    float m_k;

    float m_restLength;

public:
    Spring(RigidBody& other, float k, float restLength);

    ~Spring();

    // apply Hooke's law based on objects positions
    void UpdateForce(RigidBody* rigidBody, float duration) override;

};

