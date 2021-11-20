#pragma once

#include "../RigidBody.h"

class ParticleForceGenerator
{
public:
	virtual void UpdateForce(RigidBody* rigidBody, float duration) = 0;
};

