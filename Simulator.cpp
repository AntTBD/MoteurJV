#include "Simulator.h"

Simulator::Simulator()
{
    this->particleForceRegistry = ParticleForceRegistry();
    this->particleGravityGenerator = ParticleGravity();
    this->particleSpringGenerator = nullptr;

    this->particleContactRegistry = ParticleContactRegistry();
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
        // ------ add contacts -------
        // add contacts naive entre particules (=colision entre 2 particules)
        NaiveParticleContactGenerator* naiveParticleContactGenerator = new NaiveParticleContactGenerator(&particles, 10);// contacts entre particules de rayon 10
        this->particleContactRegistry.Add(naiveParticleContactGenerator, 2 * this->particles.size());
        // contact avec le sol
        GroundContactGenerator* groundContactGenerator = new GroundContactGenerator(&particles, 0.0f);// contact avec le sol à une hauteur de 0
        this->particleContactRegistry.Add(groundContactGenerator, this->particles.size());


        for (int i = 0; i < this->particles.size(); i++)
        {
            // ------ force -------
            // add ressort ancré sur la particule actuelle
            this->particleSpringGenerator = new ParticleSpring(*this->particles[i], 5, 50);

            // add tiges or cables between each particles + spring force anchored on actual particle
            for (int k = i + 1; k < this->particles.size(); k++) {
                // ------ contacts -------
                // add contacts cables
                //auto tige = new ParticleRod(this->particles[i], this->particles[k], 100);// tige de longueur 200
                //this->particleContactRegistry.Add(tige, 1);

                // add contacts tiges
                auto cable = new ParticleCable(this->particles[i], this->particles[k], 100);// cable de longueur 200
                this->particleContactRegistry.Add(cable, 1);

                // ------ force -------
                // Add spring force
                this->particleForceRegistry.Add(this->particles[k], this->particleSpringGenerator);
            }

            // ------ force -------
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
            this->particleContactRegistry.UpdateContacts();

            // 4 - Resolve contacts
            this->particleContactRegistry.Resolve(deltaTime);

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

    this->particleContactRegistry.Clear();

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
bool Simulator::isUpdated() const
{
    return isUpdateFinished;
}