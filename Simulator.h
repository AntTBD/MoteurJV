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
#include "GroundContactGenerator.h"
#include "ParticleSpring.h"

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

	NaiveParticleContactGenerator* particleContactGenerator;
	std::vector<ParticleRod*> cables;
	GroundContactGenerator* groundContactGenerator;
	ParticleContactResolver* particleContactResolver;

	bool isPaused = false;
	bool isUpdateFinished = false;
public:
	float dT;
	Simulator();

	void AddParticle(Particle* p); // Add particle to simulator
	Particle* GetParticle(int id);
	void Print(); // Print all the particules of the simulation to the console

	void Update(float deltaTime); // Update acceleration, speed and position of all particles in the simulator
	void Pause();
	void Resume();
	void ClearParticles(); // Remove all particles from simulator
	const std::vector<Particle*>& GetParticles() const;
	bool isUpdated();


};