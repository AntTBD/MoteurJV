#include "ParticleContact.h"

ParticleContact::ParticleContact()
{
	this->m_rigidBody[0] = new RigidBody();
	this->m_rigidBody[1] = new RigidBody();

	this->m_contactNormal = Vector3(0, 0, 0);
}

ParticleContact::ParticleContact(RigidBody* rigidBody1, float restitution, float penetration) :
	m_restitution(restitution), m_penetration(penetration)
{
	this->m_rigidBody[0] = rigidBody1;
	this->m_rigidBody[1] = nullptr;

	this->m_contactNormal = Vector3(0, 1, 0);
}

ParticleContact::ParticleContact(RigidBody* rigidBody1, RigidBody* rigidBody2, float restitution, float penetration, bool inverseNormal) :
	m_restitution(restitution), m_penetration(penetration)

{
	this->m_rigidBody[0] = rigidBody1;
	this->m_rigidBody[1] = rigidBody2;

	// normal = (pa-pb).normalized
	this->m_contactNormal = (this->m_rigidBody[0]->GetPosition() - this->m_rigidBody[1]->GetPosition()).Normalized(); // diapo Gestion des collision - p5
	
	if (inverseNormal) {
		this->m_contactNormal *= -1;
	}
}

ParticleContact::~ParticleContact()
{
	this->m_rigidBody[0] = nullptr;
	this->m_rigidBody[1] = nullptr;
}

void ParticleContact::resolve(float duration)
{
	this->resolveVelocity();
	this->resolveInterpenetration();
}

float ParticleContact::calculateSeparatingVelocity() // diapo Gestion des collision - p5 
{
	Vector3 velocity = this->m_rigidBody[0]->GetVelocity();
	if (this->m_rigidBody[1] != nullptr) {
		velocity -= this->m_rigidBody[1]->GetVelocity();
	}

	return velocity.DotProduct(this->m_contactNormal);
}

void ParticleContact::resolveVelocity() // Application de l’impulsion diapo p12
{
	float k;

	// calcul du numerator
	float v_rel_Dot_n = calculateSeparatingVelocity(); // on utilise le calcul de la velocite

    // Check if it needs to be resolved.
    if (v_rel_Dot_n > 0) {
        // The contact is either separating, or stationary; there’s
        // no impulse required.
        return;
    }

    float e = this->m_restitution;
	k = (e + 1) * v_rel_Dot_n;

	// calcul du denominator
	float somInvMass = this->m_rigidBody[0]->GetInvMass();
	if (this->m_rigidBody[1] != nullptr) {
		somInvMass += this->m_rigidBody[1]->GetInvMass();
	}
    // If all particles have infinite mass, then impulses have no effect.
    if (somInvMass <= 0) return;

	//     (e + 1)  v_rel . n
	// k = -------------------     avec n . n = 1 car n unitaire
	//     (1/m1 + 1/m2) n . n
	k = (float)k / somInvMass;

	// ----- update velocity -----
	// Comme les deux particules subiront la même magnitude d’impulsion 
	// mais avec la normal inversé, on obtient :
	// particule 1 : v1' = v1 - k * n / m1
	this->m_rigidBody[0]->SetVelocity(this->m_rigidBody[0]->GetVelocity() - k * this->m_contactNormal * this->m_rigidBody[0]->GetInvMass());
	// particule 2 (if exist) : v2' = v2 + k * n / m2
	if (this->m_rigidBody[1] != nullptr) {
		this->m_rigidBody[1]->SetVelocity(this->m_rigidBody[1]->GetVelocity() + k * this->m_contactNormal * this->m_rigidBody[1]->GetInvMass());
	}
	//std::cout << "k: " << k << std::endl;
}

void ParticleContact::resolveInterpenetration() // Résolution d’interpénétration diapo p15
{
	if (m_penetration > 0) {

		float somInvMass = this->m_rigidBody[0]->GetInvMass();
		if (this->m_rigidBody[1] != nullptr) {
			somInvMass += this->m_rigidBody[1]->GetInvMass();
		}
        // If all particles have infinite mass, then we do nothing.
        if (somInvMass <= 0) return;

		// particule 1 : p' = p + m2 / (m1+m2) * d * n
		this->m_rigidBody[0]->SetPosition(this->m_rigidBody[0]->GetPosition() + (1.0f/this->m_rigidBody[0]->GetInvMass()) * somInvMass * m_penetration * this->m_contactNormal);
		// particule 2 (if exist) : p' = p + (- m2 / (m1+m2)) * d * n
		if (this->m_rigidBody[1] != nullptr) {
			this->m_rigidBody[1]->SetPosition(this->m_rigidBody[1]->GetPosition() - (1.0f / this->m_rigidBody[1]->GetInvMass()) * somInvMass * m_penetration * this->m_contactNormal);
		}
	}
}
