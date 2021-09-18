#include <math.h>
#include <assert.h>
#include "Particle.h"

// Constructors
Particle::Particle()
{
	this->position = Vector3();
	this->speed = Vector3();
	this->acceleration = Vector3();
}

Particle::Particle(Vector3 pos, Vector3 sp, Vector3 acc)
{
	this->position = pos;
	this->speed = sp;
	this->acceleration = acc;
}

Particle::Particle(const Particle& particle)
{
	this->position = particle.GetPosition();
	this->speed = particle.GetSpeed();
	this->acceleration = particle.GetAcceleration();
}

// Operator
std::ostream& operator<< (std::ostream& os, const Particle& particle)
{
	os << "Acceleration : " << particle.GetAcceleration() << ", Speed : " << particle.GetSpeed() << ", Position : " << particle.GetPosition();
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

// Functions
void Particle::Update(float dTime)
{
	this->speed = this->speed + this->acceleration * dTime;
	this->position = this->position + this->speed * dTime;
}