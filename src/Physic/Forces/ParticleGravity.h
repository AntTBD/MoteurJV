#pragma once
#include "ParticleForceGenerator.h"

class ParticleGravity : public ParticleForceGenerator
{
private:
	Vector3 m_gravity;

public:
	//Constructors
	ParticleGravity();
	ParticleGravity(Vector3 gravity);

	//Getterss & Setters
	Vector3 GetGravity() const;
	void SetGravity(Vector3 gravity);

	//Functions
	// F = particule->GetMass() * m_gravity
	void UpdateForce(RigidBody* rigidBody, float duration) override;
};

