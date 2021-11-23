#include "Drag.h"

Drag::Drag(float k1, float k2) : m_k1(k1), m_k2(k2) {}

Drag::~Drag() {}

void Drag::UpdateForce(RigidBody* rigidBody, float duration)
{
	// En jeu vidéo, on peut utiliser une formule simplifiée :
	// f_drag = - v.normalized() * ( k1 * |v| + k2 * |v|² )
	rigidBody->AddForce(rigidBody->GetVelocity().Normalized() * -(this->m_k1 * rigidBody->GetVelocity().Magnitude() + this->m_k2 * rigidBody->GetVelocity().SquaredMagnitude()));
}
