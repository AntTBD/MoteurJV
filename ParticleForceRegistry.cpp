#include "ParticleForceRegistry.h"


ParticleForceRegistry::ParticleForceEntry::ParticleForceEntry(Particle* particle, ParticleForceGenerator* forceGenerator) : particle(particle), forceGenerator(forceGenerator){}


void ParticleForceRegistry::Add(Particle* particle, ParticleForceGenerator* forceGenerator)
{
	registry.push_back(ParticleForceRegistry::ParticleForceEntry(particle, forceGenerator));

}

void ParticleForceRegistry::UpdateForce(float duration)
{
	for (ParticleForceEntry entry : registry)
	{
		entry.forceGenerator->UpdateForce(entry.particle, duration);
	}
}

void ParticleForceRegistry::Clear()
{
	registry.clear();
}
