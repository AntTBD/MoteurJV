#pragma once
#include <vector>
#include <thread>
#include "Particle.h"
// forces
#include "ParticleContactResolver.h"
#include "ParticleForceRegistry.h"
#include "ParticleGravity.h"
#include "ParticleSpring.h"
// contacts
#include "ParticleContactRegistry.h"
#include "NaiveParticleContactGenerator.h"
#include "GroundContactGenerator.h"
#include "ParticleCable.h"
#include "ParticleRod.h"

/// <summary>
/// Our World with multiple particles
/// </summary>
class Simulator
{
private:
	std::vector<Particle*> particles; // Vector holding all the particles in our simulation
	
	ParticleForceRegistry particleForceRegistry;
	ParticleGravity particleGravityGenerator;
	ParticleSpring* particleSpringGenerator;

	ParticleContactRegistry particleContactRegistry;

	bool isPaused = false;
	bool isUpdateFinished = false;
public:
	float dT;
	Simulator();

	void AddParticle(Particle* p); // Add particle to simulator
	Particle* GetParticle(int id);
	void Print(); // Print all the particules of the simulation to the console

	void Start();
	void Update(float deltaTime); // Update acceleration, speed and position of all particles in the simulator
	void Pause();
	void Resume();
	void ClearParticles(); // Remove all particles from simulator
	const std::vector<Particle*>& GetParticles() const;
	bool isUpdated();


};