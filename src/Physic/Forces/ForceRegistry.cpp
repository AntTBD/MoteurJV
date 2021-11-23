#include "ForceRegistry.h"

ForceRegistry::ForceEntry::ForceEntry(RigidBody* rigidBody, ForceGenerator* forceGenerator) : rigidBody(rigidBody), forceGenerator(forceGenerator) {}


void ForceRegistry::Add(RigidBody* rigidBody, ForceGenerator* forceGenerator)
{
	this->m_registry.push_back(ForceRegistry::ForceEntry(rigidBody, forceGenerator));
}

void ForceRegistry::UpdateForce(float duration)
{
	for (ForceEntry entry : this->m_registry )
	{
		entry.forceGenerator->UpdateForce(entry.rigidBody, duration);
	}
}

void ForceRegistry::Clear()
{
	this->m_registry.clear();
}
