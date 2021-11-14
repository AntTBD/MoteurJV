#pragma once
#include <vector>
#include <thread>
#include "../src/Physic/Particle.h"
// forces
#include "../src/Physic/Contacts/ParticleContactResolver.h"
#include "../src/Physic/Forces/ParticleForceRegistry.h"
#include "../src/Physic/Forces/ParticleGravity.h"
#include "../src/Physic/Forces/ParticleSpring.h"
// contacts
#include "../src/Physic/Contacts/ParticleContactRegistry.h"
#include "../src/Physic/Contacts/NaiveParticleContactGenerator.h"
#include "../src/Physic/Contacts/GroundContactGenerator.h"
#include "../src/Physic/Contacts/ParticleCable.h"
#include "../src/Physic/Contacts/ParticleRod.h"

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
	bool isUpdated() const;


};