#include "ParticleForceRegistry.h"

ParticleForceRegistry::ParticleForceEntry::ParticleForceEntry(RigidBody* rigidBody, ParticleForceGenerator* forceGenerator) : rigidBody(rigidBody), forceGenerator(forceGenerator) {}


void ParticleForceRegistry::Add(RigidBody* rigidBody, ParticleForceGenerator* forceGenerator)
{
	this->m_registry.push_back(ParticleForceRegistry::ParticleForceEntry(rigidBody, forceGenerator));
}

void ParticleForceRegistry::UpdateForce(float duration)
{
	for (ParticleForceEntry entry : this->m_registry )
	{
		entry.forceGenerator->UpdateForce(entry.rigidBody, duration);
	}
}

void ParticleForceRegistry::Clear()
{
	this->m_registry.clear();
}
