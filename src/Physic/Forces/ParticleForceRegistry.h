#pragma once
#include "ForceGenerator.h"

#include <vector>

class ParticleForceRegistry
{
private:
	struct ParticleForceEntry
	{
        RigidBody* rigidBody;
		ForceGenerator* forceGenerator;
		ParticleForceEntry(RigidBody* rigidBody, ForceGenerator* forceGenerator);

	};
	using Registry = std::vector<ParticleForceEntry>;
	Registry  m_registry;
public:
	// ... Registry Accessors
	void Add(RigidBody* rigidBody, ForceGenerator* forceGenerator);
	void UpdateForce(float duration);
	void Clear();
};

