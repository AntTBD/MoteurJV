#pragma once
#include <vector>
#include <thread>
#include "Particle.h"

class Simulator
{
private:
	std::vector<Particle> particles;
	int size = 0;

public:
	void AddParticle(const Particle p);
	void Print();
	bool Update(float deltaTime);
	void ClearParticles();
	int GetSize();
	Vector3 GetParticlePosition(int i);
	std::vector<Particle> GetParticles();
	
};