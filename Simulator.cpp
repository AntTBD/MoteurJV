#include "Simulator.h"

Simulator::Simulator()
{
    this->particleForceRegistry = ParticleForceRegistry();
    this->particleGravityGenerator = ParticleGravity();
    this->particleSpringGenerator = nullptr;
    this->particleContactGenerator = new NaiveParticleContactGenerator(&particles, 5);
    this->groundContactGenerator = new WallContactGenerator(&particles, 0.0f);
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
    if (!particles.empty())
    {
        if (!this->isPaused) // No update if simulator is paused
        {

            isUpdateFinished = false;

            // add ressort ancré sur la 1ère particule
            this->particleSpringGenerator = new ParticleSpring(*this->particles[0], 5, 50);

            for (int i = 0; i < this->particles.size(); i++)
            {
                // collision naive entre particules
                std::vector<ParticleContact*> particleContactList;
                unsigned int nbContacts = this->particleContactGenerator->addContact(&particleContactList, this->particles.size());
                if (nbContacts > 0) {
                    this->particleContactResolver->resolveContacts(particleContactList, deltaTime);

                }
                // collision avec le sol
                std::vector<ParticleContact*> groundContactList;
                unsigned int nbGroundContacts = this->groundContactGenerator->addContact(&groundContactList, this->particles.size());
                if (nbGroundContacts > 0) {
                    this->particleContactResolver->resolveContacts(groundContactList, deltaTime);

                }

                // Add gravity force
                this->particleForceRegistry.Add(this->particles[i], &this->particleGravityGenerator);


            }
            // Add cables between first particles and others
            for (int k = 1; k < this->particles.size(); k++) {
                //auto cable = new ParticleRod(this->particles[0], this->particles[k], 2);// tige de longueur 2
                auto cable = new ParticleCable(this->particles[0], this->particles[k], 200);// cable de longueur 2
                this->cables.push_back(cable);

                // add ressort
                this->particleSpringGenerator->UpdateForce(this->particles[k], deltaTime);
            }

            //resolve contacts cables
            for (int j = 0; j < this->cables.size(); j++) {
                ParticleContact* contacts = new ParticleContact();// fonctionne avec 2 particules pour le moment
                unsigned int nbContacts = this->cables[j]->addContact(contacts, 2 * this->particles.size());// fonctionne avec 2 particules pour le moment
                if (nbContacts > 0) {
                    std::vector<ParticleContact*> particleContactList;
                    particleContactList.push_back(contacts);
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