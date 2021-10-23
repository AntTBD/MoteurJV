#include "WallContactGenerator.h"

WallContactGenerator::WallContactGenerator(std::vector<Particle*>* particles, float positionY):
	particles(particles), positionY(positionY)
{
}



WallContactGenerator::~WallContactGenerator()
{
}

unsigned int WallContactGenerator::addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const
{
	int iteration = 0;
	for (Particle* particle : *particles) {
		if (iteration >= limit) {
			return limit;
		}
		if (particle->GetPosition().GetY() < this->positionY) {
			contacts->push_back(new ParticleContact(particle, 0, this->positionY - particle->GetPosition().GetY()));
			iteration++;
		}
	}
	return iteration;
}
