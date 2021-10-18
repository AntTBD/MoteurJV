#pragma once
#include "ParticleForceGenerator.h"
class ParticleGravity : public ParticleForceGenerator
{
private:
	Vector3 m_gravity;

public:

	//Constructors
	ParticleGravity();
	ParticleGravity(Vector3 m_gravity);


	//Getterss & Setters
	float Get_m_Gravity() const;
	void Set_m_gravity(Vector3 m_gravity);

	//Functions

	void UpdateForce(Particle* particle, float duration);
};

