#include "ForceRegistry.h"

ForceRegistry::ParticleForceEntry::ParticleForceEntry(RigidBody* rigidBody, ForceGenerator* forceGenerator) : rigidBody(rigidBody), forceGenerator(forceGenerator) {}


void ForceRegistry::Add(RigidBody* rigidBody, ForceGenerator* forceGenerator)
{
	this->m_registry.push_back(ForceRegistry::ParticleForceEntry(rigidBody, forceGenerator));
}

void ForceRegistry::UpdateForce(float duration)
{
	for (ParticleForceEntry entry : this->m_registry )
	{
		entry.forceGenerator->UpdateForce(entry.rigidBody, duration);
	}
}

void ForceRegistry::Clear()
{
	this->m_registry.clear();
}
