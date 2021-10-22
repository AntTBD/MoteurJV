#include "WallContactGenerator.h"

WallContactGenerator::WallContactGenerator(Particle* particle, float positionY):
	particle(particle)
{
	this->wall = new Particle(Vector3(0, positionY, 0), Vector3(), 1.0f/99.0f);
}



WallContactGenerator::~WallContactGenerator()
{
}

unsigned int WallContactGenerator::addContact(ParticleContact* contact, unsigned int limit) const
{
	if (this->particle->GetPosition().GetY() < this->wall->GetPosition().GetY()) {
		*contact = ParticleContact(this->particle, this->wall, 0, this->wall->GetPosition().GetY() -this->particle->GetPosition().GetY());
		return 1;
	}

	return 0;
}
