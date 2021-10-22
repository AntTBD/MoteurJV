#pragma once
#include <vector>
#include <thread>
#include "Particle.h"
#include "ParticleContactResolver.h"
#include "ParticleForceRegistry.h"
#include "NaiveParticleContactGenerator.h"
#include "ParticleCable.h"
#include "ParticleRod.h"
#include "ParticleGravity.h"
#include "Mouse.h"

/// <summary>
/// Our World with multiple particles
/// </summary>
class Simulator
{
private:
	std::vector<Particle*> particles; // Vector holding all the particles in our simulation
	
	ParticleForceRegistry particleForceRegistry;
	ParticleGravity particleGravityGenerator;

	NaiveParticleContactGenerator* particleContactGenerator;
	std::vector<ParticleCable*> cables;
	ParticleContactResolver* particleContactResolver;

	bool isPaused = false;
	Mouse* mouse;

public:
	Simulator();

	void AddMouse(Mouse* mouse);
	void AddParticle(Particle* p); // Add particle to simulator
	void Print(); // Print all the particules of the simulation to the console

	void Update(float deltaTime); // Update acceleration, speed and position of all particles in the simulator
	void Pause();
	void Resume();
	void ClearParticles(); // Remove all particles from simulator
	const std::vector<Particle*>& GetParticles() const;


};