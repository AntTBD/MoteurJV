#include "NaiveParticleContactGenerator.h"

NaiveParticleContactGenerator::NaiveParticleContactGenerator(std::vector<Particle*> particles, float radius) : 
	particles(particles), radius(radius)
{}

NaiveParticleContactGenerator::~NaiveParticleContactGenerator() {}

unsigned int NaiveParticleContactGenerator::addContact(ParticleContact* contact, unsigned int limit) const
{
	int iteration = 0;
	for (int i = 0; i < this->particles.size(); i++) {
		for (int j = 0; j < this->particles.size(); j++) {
			if (iteration > limit) {
				return limit;
			}
			if (i == j) continue;
			float length = (this->particles[i]->GetPosition() - this->particles[j]->GetPosition()).Magnitude();
			if (length < this->radius) {
				contact = new ParticleContact(*this->particles[i], *this->particles[j], 0, this->radius - length);
				iteration++;
			}
		}
	}
	return iteration;
}
