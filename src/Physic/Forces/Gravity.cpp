#include "Gravity.h"


// Constructors
Gravity::Gravity()
{
	this->m_gravity = Vector3(0, -10, 0);
}

Gravity::Gravity(Vector3 gravity)
{
	this->m_gravity = gravity;
}


// Getters & Setters
Vector3 Gravity::GetGravity() const
{
	return this->m_gravity;
}

void Gravity::SetGravity(Vector3 gravity)
{
	this->m_gravity = gravity;
}

void Gravity::UpdateForce(RigidBody* rigidBody, float duration)
{
    rigidBody->AddForce(this->m_gravity * rigidBody->GetMass());

}
