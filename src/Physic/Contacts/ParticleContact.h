#pragma once

#include "../Particle.h"

class ParticleContact
{
public:
	// Particle[0] => Particle A
	// Particle[1] => Particle B - Could be nullptr
	Particle* m_particle[2];

	// value between 0 - 1
	// defining the elasticness of the collision
	float m_restitution;

	// distance of penetration of the contact
	float m_penetration;

	// normal of the contact
	Vector3 m_contactNormal;

	ParticleContact();
	ParticleContact(Particle* particle1, float restitution, float penetration);
	ParticleContact(Particle* particle1, Particle* particle2, float restitution, float penetration, bool inverseNormal = false);
	~ParticleContact();

	// Resolve velocity and interpenetration
	void resolve(float duration);

	// return the separationVelocity of the particle
	float calculateSeparatingVelocity();

private:
	// Handle impulse for this collision
	void resolveVelocity();

	// Handle interpenetration for this collision
	void resolveInterpenetration();
};

