#include "Buoyancy.h"

Buoyancy::Buoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity) :
	m_maxDepth(maxDepth), m_volume(volume), m_waterHeight(waterHeight), m_liquidDensity(liquidDensity) {}

Buoyancy::~Buoyancy() {}

void Buoyancy::UpdateForce(RigidBody* rigidBody, float duration)
{
	float d = (this->m_waterHeight + this->m_maxDepth - (rigidBody->GetPosition()).DotProduct(Vector3(0, 1, 0)) / (2.f * this->m_maxDepth));
	if (d <= 0) // L’objet est hors du liquide
		return;
	else if (d >= 1) // L’objet est partiellement submergé
        rigidBody->AddForce(Vector3(0, 1, 0) * (this->m_volume * this->m_liquidDensity));
	else // L’objet est complètement submergé
        rigidBody->AddForce(Vector3(0, 1, 0) * (d * this->m_volume * this->m_liquidDensity));
}
