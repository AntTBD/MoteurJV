#include "NaiveParticleContactGenerator.h"

NaiveParticleContactGenerator::NaiveParticleContactGenerator(std::vector<RigidBody*>* rigidBodies, float radius) :
	rigidBodies(rigidBodies), radius(radius)
{}

NaiveParticleContactGenerator::~NaiveParticleContactGenerator() {}

unsigned int NaiveParticleContactGenerator::addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const
{
	if (limit > 0)
	{
		int iteration = 0;
		for (int i = 0; i < this->rigidBodies->size(); i++) {
			for (int j = 0; j < this->rigidBodies->size(); j++) {
				if (iteration >= limit) {
					return limit;
				}
				if (i == j) continue;
				float length = (this->rigidBodies->at(j)->GetPosition() - this->rigidBodies->at(i)->GetPosition()).Magnitude();
				if (length <= this->radius) {
					contacts->push_back(new ParticleContact(this->rigidBodies->at(i), this->rigidBodies->at(j), 1, this->radius - length));
					iteration++;
				}
			}
		}
		return iteration;
	}
	return 0;
}
