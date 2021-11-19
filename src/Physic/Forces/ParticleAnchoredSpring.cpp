#include "ParticleAnchoredSpring.h"

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3& anchor, float k, float restLenght) :
	m_anchor(&anchor), m_k(k), m_restLenght(restLenght) {}

ParticleAnchoredSpring::~ParticleAnchoredSpring() {
    delete m_anchor;
}

void ParticleAnchoredSpring::UpdateForce(RigidBody* rigidBody, float duration)
{
	// d = xa - xb
	Vector3 d = (rigidBody->GetPosition() - *this->m_anchor);

	// f = - k * ( |d| - l0) * d.normalized
    rigidBody->AddForce(-this->m_k * (d.Magnitude() - this->m_restLenght) * d.Normalized());
}
