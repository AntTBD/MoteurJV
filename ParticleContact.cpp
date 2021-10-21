#include "ParticleContact.h"

ParticleContact::ParticleContact(Particle& particle1, float restitution, float penetration) :
	m_restitution(restitution), m_penetration(penetration)
{
	this->m_particle[0] = &particle1;
	this->m_particle[1] = nullptr;

	this->m_contactNormal = Vector3(0, 1, 0);
}

ParticleContact::ParticleContact(Particle& particle1, Particle& particle2, float restitution, float penetration) :
	m_restitution(restitution), m_penetration(penetration)

{
	this->m_particle[0] = &particle1;
	this->m_particle[1] = &particle2;

	this->m_contactNormal = (this->m_particle[0]->GetPosition() - this->m_particle[1]->GetPosition()).Normalize();
}

ParticleContact::~ParticleContact()
{
	this->m_particle[0] = nullptr;
	this->m_particle[1] = nullptr;
}

void ParticleContact::resolve(float duration)
{
	this->resolveVelocity();
	this->resolveInterpenetration();
}

float ParticleContact::calculateSeparatingVelocity() // diapo Gestion des collision - p5 
{
	Vector3 velocity = this->m_particle[0]->GetSpeed();
	if (this->m_particle[1] != nullptr) {
		velocity -= this->m_particle[1]->GetSpeed();
	}

	return velocity.DotProduct(this->m_contactNormal);
}

void ParticleContact::resolveVelocity() // Application de l�impulsion diapo p12
{
	float k;

	// calcul du numerator
	float v_rel_Dot_n = calculateSeparatingVelocity(); // on utilise le calcul de la velocite
	float e = this->m_restitution;
	k = (e + 1) * v_rel_Dot_n;

	// calcul du denominator
	float somInvMass = this->m_particle[0]->GetinvMass();
	if (this->m_particle[1] != nullptr) {
		somInvMass += this->m_particle[1]->GetinvMass();
	}

	//     (e + 1)  v_rel . n
	// k = -------------------
	//     (1/m1 + 1/m2) n . n
	k = k / somInvMass;

	// ----- update velocity -----
	// Comme les deux particules subiront la m�me magnitude d�impulsion 
	// mais avec la normal invers�, on obtient :
	// particule 1 : v' = v - k * n / m
	this->m_particle[0]->SetSpeed(this->m_particle[0]->GetSpeed() - this->m_contactNormal * this->m_particle[0]->GetinvMass() * k);
	// particule 2 (if exist) : v' = v + k * n / m
	if (this->m_particle[1] != nullptr) { 
		this->m_particle[1]->SetSpeed(this->m_particle[1]->GetSpeed() + this->m_contactNormal * this->m_particle[1]->GetinvMass() * k);
	}
}

void ParticleContact::resolveInterpenetration() // R�solution d�interp�n�tration diapo p15
{
	if (m_penetration > 0) {

		float somInvMass = this->m_particle[0]->GetinvMass();
		if (this->m_particle[1] != nullptr) {
			somInvMass += this->m_particle[1]->GetinvMass();
		}

		// particule 1 : Dp = m2 / (m1+m2) * d * n
		this->m_particle[0]->SetPosition(this->m_contactNormal * (1.0f/this->m_particle[0]->GetinvMass()) * somInvMass * m_penetration);
		// particule 2 (if exist) : Dp = - m2 / (m1+m2) * d * n
		if (this->m_particle[1] != nullptr) {
			this->m_particle[1]->SetPosition(this->m_contactNormal * (-1.0f / this->m_particle[1]->GetinvMass()) * somInvMass * m_penetration);
		}
	}
}
