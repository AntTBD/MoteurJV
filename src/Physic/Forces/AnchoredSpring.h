#pragma once

#include "ForceGenerator.h"

class AnchoredSpring : public ForceGenerator
{
private:
    //other anchor
    Vector3* m_anchor;

    // Spring constant
    float m_k;

    float m_restLenght;

public:
    AnchoredSpring(Vector3& anchor, float k, float restLenght);

    ~AnchoredSpring();

    // apply Hooke's law based on particles positions
    void UpdateForce(RigidBody* rigidBody, float duration) override;

};

