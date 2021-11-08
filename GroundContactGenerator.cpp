#include "GroundContactGenerator.h"

GroundContactGenerator::GroundContactGenerator(std::vector<Particle*>* particles, float positionY):
	particles(particles), positionY(positionY)
{
}



GroundContactGenerator::~GroundContactGenerator()
{
}

unsigned int GroundContactGenerator::addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const
{
	if (limit > 0)
	{
		int iteration = 0;
		for (Particle* particle : *this->particles) {
			if (iteration >= limit) {
				return limit;
			}
			if (particle->GetPosition().GetY() < this->positionY) {
				contacts->push_back(new ParticleContact(particle, 1, this->positionY - particle->GetPosition().GetY()));
				iteration++;
			}
		}
		return iteration;
	}
	return 0;
}
