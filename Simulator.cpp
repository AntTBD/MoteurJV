#include "Simulator.h"


void Simulator::AddParticle(const Particle p)
{
	this->particles.push_back(p);
}


void Simulator::Update()
{
    while (this->isOn)
    {
        if (!particles.empty())
        {
            for (int i = 0; i < particles.size(); i++)
            {
                particles[i].Integrate(0.2f);
                std::cout << "Particule " << i + 1 << " : " << particles[i] << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

    }
}

void Simulator::Stop() {
    this->isOn = false;
}