#pragma once
#include <vector>
#include <thread>
#include "Particle.h"

class Simulator
{
private:
	std::vector<Particle> particles;

public:
	void AddParticle(const Particle p);
	void Print();
	bool Update();
	void ClearParticles();
	
};