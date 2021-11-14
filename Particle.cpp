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
	this->sumForces = Vector3();
}

Particle::Particle(Vector3 position, Vector3 speed, float invMass)
{
	this->position = position;
	this->speed = speed;
	this->invMass = invMass;
}

Particle::Particle(const Particle& particle)
{
	this->position = particle.GetPosition();
	this->speed = particle.GetSpeed();
	this->invMass = particle.GetinvMass();
	this->sumForces = particle.GetSumForces();
	this->acceleration = particle.GetAcceleration();
}

std::string Particle::toString() const
{
    std::stringstream stream;
    stream << *this;
    return stream.str();
}

// Operator
std::ostream& operator<< (std::ostream& os, const Particle& particle)
{
	try {
		os << "Mass : " << 1.0f / particle.GetinvMass() << ", Acceleration : " << particle.GetAcceleration() << ", Speed : " << particle.GetSpeed() << ", Position : " << particle.GetPosition() << ", SumForces : " << particle.GetSumForces();

	}
	catch (std::exception ex)
	{
		os << "Error Particle.ToString(): " << ex.what();
	};
	
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

// Functions
void Particle:: AddForce(Vector3 force)
{
	this->sumForces += force;
}

void Particle::Integrate(float dTime)
{
	// 1 - Update position : p' = p + v * t + 1/2 * a * t�
	//                  OU   p' = p + v * t
	this->position = this->position + this->speed * dTime;

	// 2 - Update acceleration : a = 1/m * f
	UpdateAcceleration();

	// 3 - Update speed : v' = v * dt + a * t
	this->speed = (this->speed + this->acceleration * dTime) * this->damping;
	
	// Put sumforces back to 0 because we work with impulsions
	sumForces.SetZero();
}

void Particle::UpdateAcceleration()
{
	// Update acceleration with sumForces, invMass
	this->acceleration = this->sumForces;
}
/*
const char *Particle::toString() {
    return "Mass : ", std::string(1.0f / this->GetinvMass()) , ", Acceleration : ", std::string(this->GetAcceleration()), ", Speed : ", std::string(this->GetSpeed()), ", Position : ", std::string(this->GetPosition()), ", SumForces : ", std::string(this->GetSumForces());
}*/
