#include "ParticleForceRegistry.h"

ParticleForceRegistry::ParticleForceEntry::ParticleForceEntry(Particle* particle, ParticleForceGenerator* forceGenerator) : particle(particle), forceGenerator(forceGenerator) {}


void ParticleForceRegistry::Add(Particle* particle, ParticleForceGenerator* forceGenerator)
{
	this->m_registry.push_back(ParticleForceRegistry::ParticleForceEntry(particle, forceGenerator));
}

void ParticleForceRegistry::UpdateForce(float duration)
{
	for (ParticleForceEntry entry : this->m_registry )
	{
		entry.forceGenerator->UpdateForce(entry.particle, duration);
	}
}

void ParticleForceRegistry::Clear()
{
	this->m_registry.clear();
}
