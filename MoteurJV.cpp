#include <iostream>
#include <chrono>
#include <thread>
#include "Particle.h"
#include "Vector3.h"

int main()
{
    Vector3 initialPosition(0, 0, 1000);
    Vector3 initialSpeed(0, 0, 0);
    Vector3 acceleration(0, 0, -9.81);

    Particle particle(initialPosition, initialSpeed, acceleration);

    float dTime = 0;

    while (particle.GetPosition().GetZ() > 0)
    {
        auto start = std::chrono::system_clock::now();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        particle.Update(dTime);

        auto end = std::chrono::system_clock::now();
        auto duration = end - start;
        auto seconds = std::chrono::duration_cast<std::chrono::duration<float>>(duration);
        dTime = seconds.count();

        std::cout << particle << std::endl;
    }
}