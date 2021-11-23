#pragma once
#include "ForceGenerator.h"

class ParticleGravity : public ForceGenerator
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

