#include "ParticleDrag.h"

ParticleDrag::ParticleDrag(float k1, float k2) : m_k1(k1), m_k2(k2) {}

ParticleDrag::~ParticleDrag() {}

void ParticleDrag::updateForce(Particle* particle, float duration)
{
	particle->AddForce(particle->GetSpeed().Normalize() * -(this->m_k1 * particle->GetSpeed().Magnitude() + this->m_k2 * particle->GetSpeed().SquaredMagnitude()));
}
