#include "Simulator.h"

Simulator::Simulator()
{
    std::vector<Particle>();
}

void Simulator::AddParticle(const Particle p) // add particle to the simulator
{
	this->particles.push_back(p);
}

void Simulator::Print() // print each particle in the console
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

void Simulator::Update(float deltaTime) // update each particles until they go under 0 in y axis
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

void Simulator::ClearParticles() // clear the particle vector
{
    this->particles.clear();
}

std::vector<Particle> Simulator::GetParticles()
{
    return this->particles;
}