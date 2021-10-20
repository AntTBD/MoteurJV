#include "ParticleForceRegistry.h"




void ParticleForceRegistry::Add(Particle* particle, ParticleForceGenerator* forceGenerator)
{
	m_registry.push_back(ParticleForceRegistry::ParticleForceEntry(particle, forceGenerator));

}

void ParticleForceRegistry::UpdateForce(float duration)
{
	for (ParticleForceEntry entry : m_registry )
	{
		entry.forceGenerator->UpdateForce(entry.particle, duration);
	}
}

void ParticleForceRegistry::Clear()
{
	m_registry.clear();
}
