#include "Simulator.h"

Simulator::Simulator()
{
    this->particleForceRegistry = ParticleForceRegistry();
    this->particleGravityGenerator = ParticleGravity();
    this->particleContactGenerator = new NaiveParticleContactGenerator(&particles, 1);
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
    if (!particles.empty())
    {
        if (!this->isPaused) // No update if simulator is paused
        {

            for (int i = 0; i < this->particles.size(); i++)
            {
                // collision naive entre particules
                std::vector<ParticleContact*> particleContactList;
                unsigned int nbContacts = this->particleContactGenerator->addContact(particleContactList, 1);
                if (nbContacts > 0) {
                    this->particleContactResolver->resolveContacts(particleContactList, deltaTime);

                }


                // Add cables
                for (int k = i + 1; k < this->particles.size(); k++) {
                    //auto cable = new ParticleRod(this->particles[i], this->particles[k], 2);// tige de longueur 2
                    auto cable = new ParticleCable(this->particles[i], this->particles[k], 2);// cable de longueur 2
                    this->cables.push_back(cable);
                }

                // Add gravity force
                this->particleForceRegistry.Add(this->particles[i], &this->particleGravityGenerator);


            }
            //resolve contacts
            for (int j = 0; j < this->cables.size(); j++) {
                ParticleContact contacts[2 * 2] = {};// fonctionne avec 2 particules pour le moment
                unsigned int nbContacts = this->cables[j]->addContact(contacts, 2 * 2);// fonctionne avec 2 particules pour le moment
                if (nbContacts > 0) {
                    std::vector<ParticleContact*> particleContactList;
                    for (unsigned int l = 0; l < nbContacts; l++) {
                        particleContactList.push_back(&contacts[l]);
                    }
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