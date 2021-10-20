#include "ParticleSpring.h"

ParticleSpring::ParticleSpring(Particle& other, float k, float restLength) : m_other(&other), m_k(k), m_restLength(restLength) {}

ParticleSpring::~ParticleSpring()
{
    delete m_other;
}

// apply Hooke's law based on particles positions
void ParticleSpring::UpdateForces(Particle* particle, float duration)
{
    Vector3 d = particle->GetPosition() - m_other->GetPosition();
    particle->AddForce(d.Normalize() * (-m_k * (d.Magnitude() - m_restLength)));
}
