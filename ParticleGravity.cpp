#include "ParticleGravity.h"


// Constructors
ParticleGravity::ParticleGravity()
{
	this->m_gravity = Vector3(0, -10, 0);
}

ParticleGravity::ParticleGravity(Vector3 m_gravity)
{
	this->m_gravity = m_gravity
}


// Getters & Setters
float ParticleGravity::Get_m_Gravity() const
{
	return this->m_gravity;
}

void ParticleGravity::Set_m_gravity(Vector3 m_gravity)
{
	this->m_gravity = m_gravity;
}

void ParticleGravity::UpdateForce(Particle* particle, float duration)
{
}
