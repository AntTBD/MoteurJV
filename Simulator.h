#pragma once
#include <vector>
#include <thread>
#include "Particle.h"

class Simulator
{
private:
	std::vector<Particle> particles;
	bool isOn = true;

public:
	void AddParticle(const Particle p);
	void Update();
	void Stop();
};