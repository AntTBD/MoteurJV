#include "WallContactGenerator.h"

WallContactGenerator::WallContactGenerator(Particle* particle):
	particle(particle)
{
	this->wall = new Particle(Vector3(), Vector3(), 1.0f/99.0f, 0);
}



WallContactGenerator::~WallContactGenerator()
{
}

unsigned int WallContactGenerator::addContact(ParticleContact* contact, unsigned int limit) const
{
	if (this->particle->GetPosition().GetY() <= 0) {
		contact = new ParticleContact(*this->particle, *this->wall, 0, -this->particle->GetPosition().GetY());
		return 1;
	}

	return 0;
}
