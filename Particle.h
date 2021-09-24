#pragma once
#include <iostream>
#include "Vector3.h"

class Particle
{
private:
	Vector3 position, speed, acceleration;

	Vector3 sumForces = Vector3();
	float invMass;
	float damping = 0.999;
	float gravityFactor;

public:
	Particle();
	Particle(Vector3 pos, Vector3 sp, float invMass, float gravityFactor = 1.0);
	Particle(const Particle& particle);

	Vector3 GetPosition() const;
	Vector3 GetSpeed() const;
	Vector3 GetAcceleration() const;
	float GetinvMass() const;
	float GetGravityFactor() const;
	Vector3 GetSumForces() const;

	void SetPosition(Vector3 pos);
	void SetSpeed(Vector3 sp);
	void SetAcceleration(Vector3 acc);
	void SetInvMass(float invMass);
	void SetGravityFactor(float gravityFactor);

	void AddForce(Vector3 force);
	void Integrate(float dTime);
	void UpdateAcceleration();
};

std::ostream& operator<< (std::ostream& os, const Particle& particle);