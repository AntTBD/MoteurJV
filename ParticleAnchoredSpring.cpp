#include "ParticleAnchoredSpring.h"

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3& anchor, double k, double restLenght) :
	m_anchor(&anchor), m_k(k), m_restLenght(restLenght) {}

ParticleAnchoredSpring::~ParticleAnchoredSpring() {}

void ParticleAnchoredSpring::UpdateForce(Particle* particle, float duration)
{
	// d = xa - xb
	Vector3 d = (particle->GetPosition() - *this->m_anchor);

	// f = - k * ( |d| - l0) * d.normalized
	particle->AddForce(-this->m_k * (d.Magnitude() - this->m_restLenght) * d.Normalized());
}
