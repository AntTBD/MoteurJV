#pragma once

#include "ForceGenerator.h"

class Buoyancy : public ForceGenerator
{
private:
    // particule properties
    float m_maxDepth;
    float m_volume;

    // effect properties
    float m_waterHeight;
    float m_liquidDensity;

public:
    Buoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity = 1000.0f);
    ~Buoyancy();

    // apply Buoyancy based on particle position
    void UpdateForce(RigidBody* rigidBody, float duration) override;
};

