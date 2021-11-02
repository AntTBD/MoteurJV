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

void Simulator::Start() {
    if (!particles.empty())
    {
        for (int i = 0; i < this->particles.size(); i++)
        {            
            // add ressort ancré sur la particule actuelle
            this->particleSpringGenerator = new ParticleSpring(*this->particles[i], 5, 50);

            // add tiges or cables between each particles + spring force anchored on actual particle
            for (int k = i + 1; k < this->particles.size(); k++) {
                //auto tige = new ParticleRod(this->particles[i], this->particles[k], 100);// tige de longueur 200
                //this->tiges.push_back(tige);

                auto cable = new ParticleCable(this->particles[i], this->particles[k], 100);// cable de longueur 200
                this->cables.push_back(cable);

                // Add spring force
                this->particleForceRegistry.Add(this->particles[k], this->particleSpringGenerator);
            }

            // Add gravity force
            this->particleForceRegistry.Add(this->particles[i], &this->particleGravityGenerator);
        }
        isUpdateFinished = true;

        std::cout << "Simulation ready => start " << isUpdateFinished << std::endl;
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

            // 1 - Update force (gravity)
            this->particleForceRegistry.UpdateForce(deltaTime);

            // 2 - Integrate particles
            for (int i = 0; i < this->particles.size(); i++)
            {
                std::cout << "Particule " << i + 1 << " : " << *this->particles[i] << std::endl;
                this->particles[i]->Integrate(deltaTime);
            }

            // 3 - Add contacts
            std::vector<ParticleContact*> particleContactList;
            unsigned int nbContacts = 0;

            // add contacts naive entre particules (=colision entre 2 particules)
            nbContacts += this->particleContactGenerator->addContact(&particleContactList, 2 * this->particles.size());

            // contact avec le sol
            nbContacts += this->groundContactGenerator->addContact(&particleContactList, this->particles.size());
            
            
            // add contacts cables
            for (int j = 0; j < this->cables.size(); j++) {
                nbContacts += this->cables[j]->addContact(&particleContactList, 1);
            }

            // add contacts tiges
            for (int j = 0; j < this->tiges.size(); j++) {
                nbContacts += this->tiges[j]->addContact(&particleContactList, 1);
            }
            

            // 4 - Resolve contacts
            if (nbContacts > 0) {
                this->particleContactResolver->resolveContacts(particleContactList, deltaTime);
            }

            // clear list of contacts
            particleContactList.clear();

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
    // clear registries
    this->particleForceRegistry.Clear();

    this->cables.clear();
    this->tiges.clear();

    // delete particles
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