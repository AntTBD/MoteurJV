#include "ParticleSpring.h"

ParticleSpring::ParticleSpring(RigidBody& other, float k, float restLength) : m_other(&other), m_k(k), m_restLength(restLength) {}

ParticleSpring::~ParticleSpring()
{
    delete this->m_other;
}

// apply Hooke's law based on particles positions
void ParticleSpring::UpdateForce(RigidBody* rigidBody, float duration)
{
    // d = xa - xb
    Vector3 d = rigidBody->GetPosition() - this->m_other->GetPosition();

    // f = - k * ( |d| - l0) * d.normalized
    rigidBody->AddForce(-this->m_k * (d.Magnitude() - this->m_restLength) * d.Normalized());
}
