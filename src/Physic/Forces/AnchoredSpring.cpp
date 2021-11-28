#include "AnchoredSpring.h"

AnchoredSpring::AnchoredSpring(Vector3& anchor, float k, float restLenght) :
	m_anchor(&anchor), m_k(k), m_restLenght(restLenght) {}

AnchoredSpring::~AnchoredSpring() {
    delete m_anchor;
}

void AnchoredSpring::UpdateForce(RigidBody* rigidBody, float duration)
{
	// d = xa - xb
	Vector3 d = (rigidBody->GetPosition() - *this->m_anchor);

	// f = - k * ( |d| - l0) * d.normalized
    rigidBody->AddForce(this->m_k * (this->m_restLenght - d.Magnitude()) * d.Normalized());
}
