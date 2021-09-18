#pragma once
#include <iostream>
#include "Vector3.h"

class Particle
{
private:
	Vector3 position, speed, acceleration;
	float mass;


public:
	Particle();
	Particle(Vector3 pos, Vector3 sp, Vector3 acc);
	Particle(const Particle& particle);

	Vector3 GetPosition() const;
	Vector3 GetSpeed() const;
	Vector3 GetAcceleration() const;
	void SetPosition(Vector3 pos);
	void SetSpeed(Vector3 sp);
	void SetAcceleration(Vector3 acc);

	void Update(float dTime);
};

std::ostream& operator<< (std::ostream& os, const Particle& particle);