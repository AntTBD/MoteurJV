#include "ParticleAnchoredSpring.h"

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3& anchor, double k, double restLenght) :
	m_anchor(&anchor), m_k(k), m_restLenght(restLenght) {}

ParticleAnchoredSpring::~ParticleAnchoredSpring() {}

void ParticleAnchoredSpring::UpdateForce(Particle* particle, float duration)
{
	Vector3 d = (particle->GetPosition() - *this->m_anchor);
	particle->AddForce(d.Normalize() * (-this->m_k * (d.Magnitude() - this->m_restLenght)));
}
