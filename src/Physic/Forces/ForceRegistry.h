#pragma once
#include "ForceGenerator.h"

#include <vector>

class ForceRegistry
{
private:
	struct ForceEntry
	{
        RigidBody* rigidBody;
		ForceGenerator* forceGenerator;
		ForceEntry(RigidBody* rigidBody, ForceGenerator* forceGenerator);

	};
	using Registry = std::vector<ForceEntry>;
	Registry  m_registry;
public:
	// ... Registry Accessors
	void Add(RigidBody* rigidBody, ForceGenerator* forceGenerator);
	void UpdateForce(float duration);
	void Clear();
};

