#include "Simulator.h"

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

bool Simulator::Update() // update each particles until they go under 0 in y axis
{
    int particlesCount = particles.size();
    int particlesFinished = 0;

    if (!particles.empty())
    {
        for (int i = 0; i < particles.size(); i++)
        {
            if (particles[i].GetPosition().GetY() > 0)
            {
                particles[i].Integrate(0.2f);
                std::cout << "Particule " << i + 1 << " : " << particles[i] << std::endl;
            }
            else
            {
                particlesFinished++;
            }
                
        }
    }

    if (particlesFinished >= particlesCount)
    {
        return false;
    }
    else {
        return true;
    }

}   

void Simulator::ClearParticles() // clear the particle vector
{
    this->particles.clear();
}
