#pragma once

#include "../RigidBody.h"

class Contact
{
public:
	// Particle[0] => Particle A
	// Particle[1] => Particle B - Could be nullptr
    RigidBody* m_rigidBody[2];

	// value between 0 - 1
	// defining the elasticness of the collision
	float m_restitution;

	// distance of penetration of the contact
	float m_penetration;

	// normal of the contact
	Vector3 m_contactNormal;

	Contact();
	Contact(RigidBody* rigidBody1, float restitution, float penetration, const Vector3& contactNormal = Vector3(0,1,0), bool inverseNormal = false);
	Contact(RigidBody* rigidBody1, RigidBody* rigidBody2, float restitution, float penetration, bool inverseNormal = false);
	~Contact();

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

