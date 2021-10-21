#include "ParticleBuoyancy.h"

ParticleBuoyancy::ParticleBuoyancy(double maxDepth, double volume, double waterHeight, double liquidDensity) :
	m_maxDepth(maxDepth), m_volume(volume), m_waterHeight(waterHeight), m_liquidDensity(liquidDensity) {}

ParticleBuoyancy::~ParticleBuoyancy() {}

void ParticleBuoyancy::UpdateForce(Particle* particle, float duration)
{
	double d = (this->m_waterHeight + this->m_maxDepth - (particle->GetPosition()).DotProduct(Vector3(0, 1, 0)) / (2 * this->m_maxDepth));
	if (d <= 0) // L�objet est hors du liquide
		return;
	else if (d >= 1) // L�objet est partiellement submerg�
		particle->AddForce(Vector3(0, 1, 0) * (this->m_volume * this->m_liquidDensity));
	else // L�objet est compl�tement submerg�
		particle->AddForce(Vector3(0, 1, 0) * (d * this->m_volume * this->m_liquidDensity));
}
