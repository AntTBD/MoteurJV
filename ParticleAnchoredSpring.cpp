#include "ParticleAnchoredSpring.h"

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3& anchor, double k, double restLenght) :
	m_anchor(&anchor), m_k(k), m_restLenght(restLenght) {}

ParticleAnchoredSpring::~ParticleAnchoredSpring() {}

void ParticleAnchoredSpring::UpdateForces(Particle* particle, float duration)
{
	Vector3 d = (particle->GetPosition() - *m_anchor);
	particle->AddForce(d.Normalize() * (-m_k * (d.Magnitude() - m_restLenght)));
}
