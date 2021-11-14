#include "ParticleSpring.h"

ParticleSpring::ParticleSpring(Particle& other, float k, float restLength) : m_other(&other), m_k(k), m_restLength(restLength) {}

ParticleSpring::~ParticleSpring()
{
    delete this->m_other;
}

// apply Hooke's law based on particles positions
void ParticleSpring::UpdateForce(Particle* particle, float duration)
{
    // d = xa - xb
    Vector3 d = particle->GetPosition() - this->m_other->GetPosition();

    // f = - k * ( |d| - l0) * d.normalized
    particle->AddForce(-this->m_k * (d.Magnitude() - this->m_restLength) * d.Normalized());
}
