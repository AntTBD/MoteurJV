#include "Simulator.h"

/// <summary>
/// Constructor
/// </summary>
Simulator::Simulator()
{
    std::vector<Particle>;
}

/// <summary>
/// Add particle to the simulator
/// </summary>
/// <param name="p"></param>
void Simulator::AddParticle(const Particle p)
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
            std::cout << "Particule " << i + 1 << " : " << particles[i] << std::endl;
        }
    }

}

/// <summary>
/// Update each particles until they go under 0 in y axis
/// </summary>
/// <param name="deltaTime"></param>
void Simulator::Update(float deltaTime)
{
    if (!particles.empty())
    {
        for (int i = 0; i < particles.size(); i++)
        {
            if (!this->isPaused) // No update if simulator is paused
            {
                particles[i].Integrate(deltaTime);
                std::cout << "Particule " << i + 1 << " : " << particles[i] << std::endl;
            }
              
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
    this->particles.clear();
}

/// <summary>
/// 
/// </summary>
/// <returns>List of all particules</returns>
std::vector<Particle> Simulator::GetParticles()
{
    return this->particles;
}