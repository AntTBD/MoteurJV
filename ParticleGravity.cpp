#include "ParticleGravity.h"


// Constructors
ParticleGravity::ParticleGravity()
{
	this->m_gravity = Vector3(0, -10, 0);
}

ParticleGravity::ParticleGravity(Vector3 gravity)
{
	this->m_gravity = gravity;
}


// Getters & Setters
Vector3 ParticleGravity::GetGravity() const
{
	return this->m_gravity;
}

void ParticleGravity::SetGravity(Vector3 gravity)
{
	this->m_gravity = gravity;
}

void ParticleGravity::UpdateForce(Particle* particle, float duration)
{
	particle->AddForce(this->m_gravity * 1.0f / particle->GetinvMass());

}
