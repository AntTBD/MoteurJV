#include "GroundContactGenerator.h"

GroundContactGenerator::GroundContactGenerator(std::vector<RigidBody*>* rigidBodies, float positionY):
	rigidBodies(rigidBodies), positionY(positionY)
{
}



GroundContactGenerator::~GroundContactGenerator()
{
	for (auto rigidBody : *this->rigidBodies) {
		delete rigidBody;
	}
	this->rigidBodies->clear();
	delete this->rigidBodies;
}

unsigned int GroundContactGenerator::addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const
{
	if (limit > 0)
	{
		int iteration = 0;
		for (auto rigidBody : *this->rigidBodies) {
			if (iteration >= limit) {
				return limit;
			}
			if (rigidBody->GetPosition().GetY() < this->positionY) {
				contacts->push_back(new ParticleContact(rigidBody, 1, this->positionY - rigidBody->GetPosition().GetY()));
				iteration++;
			}
		}
		return iteration;
	}
	return 0;
}
