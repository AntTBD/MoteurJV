#include <math.h>
#include <assert.h>
#include "Particle.h"

// Constructors
Particle::Particle()
{
	this->position = Vector3();
	this->speed = Vector3();
	this->acceleration = Vector3();

	this->invMass = 1.0;
	this->gravityFactor = 1.0;
	this->sumForces = Vector3();
	this->gravityForce = Vector3(0, 0, 0);//Vector3(0, -10, 0) * this->gravityFactor;
}

Particle::Particle(Vector3 position, Vector3 speed, float invMass, float gravityFactor)
{
	this->position = position;
	this->speed = speed;

	this->invMass = invMass;
	this->gravityFactor = gravityFactor;
	this->gravityForce = Vector3(0, 0, 0);//Vector3(0, -10, 0) * this->gravityFactor;

}

Particle::Particle(const Particle& particle)
{
	this->position = particle.GetPosition();
	this->speed = particle.GetSpeed();
	this->invMass = particle.GetinvMass();
	this->gravityFactor = particle.GetGravityFactor();
	this->gravityForce = Vector3(0, 0, 0);// Vector3(0, -10, 0)* this->gravityFactor;
	this->sumForces = particle.GetSumForces();
	this->acceleration = particle.GetAcceleration();
}

// Operator
std::ostream& operator<< (std::ostream& os, const Particle& particle)
{
	os << "Mass : " << 1.0f / particle.GetinvMass() << ", Acceleration : " << particle.GetAcceleration() << ", Speed : " << particle.GetSpeed() << ", Position : " << particle.GetPosition() << ", SumForces : " << particle.GetSumForces();
	return os;
}

// Getters and Setters
Vector3 Particle::GetPosition() const
{
	return this->position;
}

Vector3 Particle::GetSpeed() const
{
	return this->speed;
}

Vector3 Particle::GetAcceleration() const
{
	return this->acceleration;
}

float Particle::GetinvMass() const
{
	return this->invMass;
}

float Particle::GetGravityFactor() const
{
	return this->gravityFactor;
}

Vector3 Particle::GetSumForces() const
{
	return this->sumForces;
}

void Particle::SetPosition(Vector3 pos)
{
	this->position = pos;
}

void Particle::SetSpeed(Vector3 sp)
{
	this->speed = sp;
}

void Particle::SetAcceleration(Vector3 acc)
{
	this->acceleration = acc;
}

void Particle::SetInvMass(float invMass)
{
	this->invMass = invMass;
}

void Particle::SetGravityFactor(float gravityFactor)
{
	this->gravityFactor = gravityFactor;
}

// Functions
void Particle:: AddForce(Vector3 force)
{
	this->sumForces += force;
}

void Particle::Integrate(float dTime)
{
	// Update acceleration
	UpdateAcceleration();

	// Update speed
	this->speed = (this->speed + this->acceleration * dTime) * this->damping;

	// Update position
	this->position = this->position + this->speed * dTime;

	// Put sumforces back to 0 because we work with impulsions
	sumForces.SetZero();
}

void Particle::UpdateAcceleration()
{
	// Update acceleration with sumForces, invMass and add the gravityForce that is always there
	this->acceleration = this->sumForces * this->invMass + this->gravityForce;
}