#include "GroundContactGenerator.h"

GroundContactGenerator::GroundContactGenerator(std::vector<RigidBody*>* rigidBodies, float positionY, bool inverse, Vector3 normal):
	rigidBodies(rigidBodies), positionY(positionY), inverse(inverse), normal(normal)
{
    normal.Normalize();
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
            // get minimum length between 2 rgidbodies with max dimension of them (as a sphere)
            Vector3 temp(rigidBody->GetPosition().GetX() * this->normal.GetX(), rigidBody->GetPosition().GetY() * this->normal.GetY(),rigidBody->GetPosition().GetZ() * this->normal.GetZ());
            temp -= this->normal*this->positionY;

            float minlengthY =  (!this->inverse?temp.GetMaxValue():temp.GetMinValue()) + (!this->inverse ? -1.f: 1.f)* rigidBody->GetDimensions().GetMaxValue();
			if (!this->inverse && minlengthY < 0) {
				contacts->push_back(new ParticleContact(rigidBody, 1, this->positionY - minlengthY, this->normal));
				iteration++;
			}
            else if (this->inverse && minlengthY > 0) {
                contacts->push_back(new ParticleContact(rigidBody, 1, minlengthY - this->positionY, this->normal, true));
                iteration++;
            }
		}
		return iteration;
	}
	return 0;
}
