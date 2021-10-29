#include "NaiveParticleContactGenerator.h"

NaiveParticleContactGenerator::NaiveParticleContactGenerator(std::vector<Particle*>* particles, float radius) : 
	particles(particles), radius(radius)
{}

NaiveParticleContactGenerator::~NaiveParticleContactGenerator() {}

unsigned int NaiveParticleContactGenerator::addContact(std::vector<ParticleContact*>* contacts, unsigned int limit)
{
	int iteration = 0;
	for (int i = 0; i < this->particles->size(); i++) {
		for (int j = 0; j < this->particles->size(); j++) {
			if (iteration >= limit) {
				return limit;
			}
			if (i == j) continue;
			float length = (this->particles->at(i)->GetPosition() - this->particles->at(j)->GetPosition()).Magnitude();
			if (length <= this->radius) {
				contacts->push_back(new ParticleContact(this->particles->at(i), this->particles->at(j), 1, this->radius - length));
				iteration++;
			}
		}
	}
	return iteration;
}
