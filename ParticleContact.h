#pragma once

#include "Particle.h"

class ParticleContact
{
public:
	// Particle[0] => Particle A
	// Particle[1] => Particle B - Could be nullptr
	Particle* particle[2];

	// value between 0 - 1
	// defining the elasticness of the collision
	float restitution;

	// distance of penetration of the contact
	float penetration;

	// normal of the contact
	Vector3 contactNormal;

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

