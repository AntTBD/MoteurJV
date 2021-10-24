#include "Simulator.h"

Simulator::Simulator()
{
    this->particleForceRegistry = ParticleForceRegistry();
    this->particleGravityGenerator = ParticleGravity();
    this->particleSpringGenerator = nullptr;
    this->particleContactGenerator = new NaiveParticleContactGenerator(&particles, 10);// contacts entre particules de rayon 5
    this->groundContactGenerator = new GroundContactGenerator(&particles, 0.0f);// contact avec le sol à une hauteur de 0
    this->particleContactResolver = new ParticleContactResolver();
}

/// <summary>
/// Add particle to the simulator
/// </summary>
/// <param name="p"></param>
void Simulator::AddParticle(Particle* p)
{
    this->particles.push_back(p);
}

Particle* Simulator::GetParticle(int id)
{
    if (id >= 0 && id < this->particles.size())
        return this->particles.at(id);
    else
        return nullptr;
}

/// <summary>
/// Print each particle in the console
/// </summary>
void Simulator::Print()
{
    if (particles.empty())
    {
        std::cout << "No particles" << std::endl;
    }
    else
    {
        for (int i = 0; i < particles.size(); i++)
        {
            std::cout << "Particule " << i + 1 << " : " << *particles[i] << std::endl;
        }
    }

}

/// <summary>
/// Update each particles
/// </summary>
/// <param name="deltaTime"></param>
void Simulator::Update(float deltaTime)
{
    this->dT = deltaTime;
    if (!particles.empty())
    {
        if (!this->isPaused) // No update if simulator is paused
        {

            isUpdateFinished = false;

            // add ressort ancré sur la 1ère particule
            this->particleSpringGenerator = new ParticleSpring(*this->particles[0], 5, 50);

            // parcours de la liste de particles
            for (int i = 0; i < this->particles.size(); i++)
            {
                // add contacts naive entre particules (=colision entre 2 particules)
                std::vector<ParticleContact*> particleContactList;
                unsigned int nbContacts = this->particleContactGenerator->addContact(&particleContactList, this->particles.size());
                if (nbContacts > 0) {
                    this->particleContactResolver->resolveContacts(particleContactList, deltaTime);

                }
                // contact avec le sol
                std::vector<ParticleContact*> groundContactList;
                unsigned int nbGroundContacts = this->groundContactGenerator->addContact(&groundContactList, this->particles.size());
                if (nbGroundContacts > 0) {
                    this->particleContactResolver->resolveContacts(groundContactList, deltaTime);

                }

                // Add gravity force
                this->particleForceRegistry.Add(this->particles[i], &this->particleGravityGenerator);

                // add tiges or cables between each particles
                for (int k = i + 1; k < this->particles.size(); k++) {
                    if (k == i) continue;
                    //auto tige = new ParticleRod(this->particles[i], this->particles[k], 100);// tige de longueur 200
                    //this->tiges.push_back(tige);

                    auto cable = new ParticleCable(this->particles[i], this->particles[k], 100);// cable de longueur 200
                    this->cables.push_back(cable);
                }


                // add ressort ancré sur la particule actuelle
                this->particleSpringGenerator = new ParticleSpring(*this->particles[i], 5, 50);

                // Add ressort entre la particule actuelle and toutes les autres
                for (int k = i + 1; k < this->particles.size(); k++) {
                    if (k == i) continue;

                    // add ressort
                    this->particleSpringGenerator->UpdateForce(this->particles[k], deltaTime);
                }
            }

            //resolve contacts cables
            for (int j = 0; j < this->cables.size(); j++) {
                ParticleContact* contact = new ParticleContact();// fonctionne avec 2 particules pour le moment
                unsigned int nbContacts = this->cables[j]->addContact(contact, 2 * this->particles.size());// fonctionne avec 2 particules pour le moment
                if (nbContacts > 0) {
                    std::vector<ParticleContact*> particleContactList;
                    particleContactList.push_back(contact);
                    this->particleContactResolver->resolveContacts(particleContactList, deltaTime);

                }
            }

            //resolve contacts tiges
            for (int j = 0; j < this->tiges.size(); j++) {
                ParticleContact* contact = new ParticleContact();// fonctionne avec 2 particules pour le moment
                unsigned int nbContacts = this->tiges[j]->addContact(contact, 2 * this->particles.size());// fonctionne avec 2 particules pour le moment
                if (nbContacts > 0) {
                    std::vector<ParticleContact*> particleContactList;
                    particleContactList.push_back(contact);
                    this->particleContactResolver->resolveContacts(particleContactList, deltaTime);

                }
            }

            // update force (gravity)
            this->particleForceRegistry.UpdateForce(deltaTime);

            for (int i = 0; i < this->particles.size(); i++)
            {
                std::cout << "Particule " << i + 1 << " : " << *this->particles[i] << std::endl;
                this->particles[i]->Integrate(deltaTime);
            }

            this->particleForceRegistry.Clear();
            this->cables.clear();
            this->tiges.clear();

            isUpdateFinished = true;
        }
    }
}

void Simulator::Pause()
{
    this->isPaused = true;
}

void Simulator::Resume()
{
    this->isPaused = false;
}

/// <summary>
/// Clear the particle vector
/// </summary>
void Simulator::ClearParticles()
{
    for (Particle* p : this->particles)
    {
        delete(p);
    }
    this->particles.clear();
}

/// <summary>
/// 
/// </summary>
/// <returns>List of all particules</returns>
const std::vector<Particle*>& Simulator::GetParticles() const
{
    return this->particles;
}


/// <summary>
/// 
/// </summary>
/// <returns>isUpdateFinished</returns>
bool Simulator::isUpdated()
{
    return isUpdateFinished;
}