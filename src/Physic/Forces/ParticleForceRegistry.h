#pragma once
#include "ParticleForceGenerator.h"

#include <vector>

class ParticleForceRegistry
{
private:
	struct ParticleForceEntry
	{
        RigidBody* rigidBody;
		ParticleForceGenerator* forceGenerator;
		ParticleForceEntry(RigidBody* rigidBody, ParticleForceGenerator* forceGenerator);

	};
	using Registry = std::vector<ParticleForceEntry>;
	Registry  m_registry;
public:
	// ... Registry Accessors
	void Add(RigidBody* rigidBody, ParticleForceGenerator* forceGenerator);
	void UpdateForce(float duration);
	void Clear();
};

