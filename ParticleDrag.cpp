#include "ParticleDrag.h"

ParticleDrag::ParticleDrag(float k1, float k2) : m_k1(k1), m_k2(k2) {}

ParticleDrag::~ParticleDrag() {}

void ParticleDrag::updateForce(Particle* particle, float duration)
{
	// En jeu vid�o, on peut utiliser une formule simplifi�e :
	// f_drag = - v.normalized() * ( k1 * |v| + k2 * |v|� )
	particle->AddForce(-(this->m_k1 * particle->GetSpeed().Magnitude() + this->m_k2 * particle->GetSpeed().SquaredMagnitude()) * particle->GetSpeed().Normalized());
}
