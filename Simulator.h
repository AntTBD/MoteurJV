#pragma once
#include <vector>
#include <thread>
#include "Particle.h"

class Simulator
{
private:
	std::vector<Particle> particles;
	bool isPaused = false;

public:
	void AddParticle(const Particle p);
	void Print();
	void Update(float deltaTime);
	void Pause();
	void Resume();
	void ClearParticles();
	std::vector<Particle> GetParticles();
	
};