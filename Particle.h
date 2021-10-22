#pragma once
#include <iostream>
#include "Vector3.h"

class Particle
{
private:
	// Particle main attribute
	Vector3 position, speed, acceleration;
	float invMass;
	float damping = 0.99f;

	Vector3 sumForces = Vector3(); // Sum of all forces used to change acceleration

public:
	// Constructors
	Particle();
	Particle(Vector3 pos, Vector3 sp, float invMass);
	Particle(const Particle& particle);

	// Getters / Setters
	Vector3 GetPosition() const;
	Vector3 GetSpeed() const;
	Vector3 GetAcceleration() const;
	float GetinvMass() const;
	Vector3 GetSumForces() const;
	void SetPosition(Vector3 pos);
	void SetSpeed(Vector3 sp);
	void SetAcceleration(Vector3 acc);
	void SetInvMass(float invMass);

	// Functions
	void AddForce(Vector3 force); // Add a force to sumForces
	void Integrate(float dTime); // Update acceleration, speed and position based on the time interval given
	void UpdateAcceleration(); // Update acceleration based on sumForces
};

// << operator
std::ostream& operator<< (std::ostream& os, const Particle& particle);