#include "NaiveContactGenerator.h"

NaiveContactGenerator::NaiveContactGenerator(std::vector<RigidBody*>* rigidBodies, float radius) :
	rigidBodies(rigidBodies), radius(radius)
{}

NaiveContactGenerator::~NaiveContactGenerator() {}

unsigned int NaiveContactGenerator::addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const
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
                // get minimum length between 2 rgidbodies with max dimension of them (as a sphere)
                float minLength = this->rigidBodies->at(i)->GetDimensions().GetMaxValue() + this->rigidBodies->at(j)->GetDimensions().GetMaxValue();
				if (length <= minLength) {
					contacts->push_back(new ParticleContact(this->rigidBodies->at(i), this->rigidBodies->at(j), 1, minLength - length));
					iteration++;
				}
			}
		}
		return iteration;
	}
	return 0;
}
