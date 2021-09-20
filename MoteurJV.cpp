#include <iostream>
#include <chrono>
#include <thread>
#include "Particle.h"
#include "Vector3.h"

int main(int, char**)
{
    Vector3 initialPosition(0, 1000, 0);
    Vector3 initialSpeed(0, 0, 0);

    Particle particle(initialPosition, initialSpeed, 1);
    particle.AddForce(Vector3(20, 0, 0));

    while (particle.GetPosition().GetY() > 0)
    {
        auto start = std::chrono::system_clock::now();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        particle.Integrate(0.2);

        std::cout << particle << std::endl;
    }

    return 0;
}