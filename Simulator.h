#pragma once
#include <vector>
#include <thread>
#include "Particle.h"

/// <summary>
/// Our World with multiple particles
/// </summary>
class Simulator
{
private:
	std::vector<Particle> particles; // Vector holding all the particles in our simulation
	bool isPaused = false;

public:
	Simulator();

	void AddParticle(const Particle p); // Add particle to simulator
	void Print(); // Print all the particules of the simulation to the console

	void Update(float deltaTime); // Update acceleration, speed and position of all particles in the simulator
	void Pause();
	void Resume();
	void ClearParticles(); // Remove all particles from simulator
	std::vector<Particle> GetParticles();
	
};