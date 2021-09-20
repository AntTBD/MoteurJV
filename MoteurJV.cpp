#include <iostream>
#include <chrono>
#include <thread>
#include "Particle.h"
#include "Vector3.h"

std::atomic_bool stopThreads = false;

void updateObj(Particle particle) {

    float dTime = 0;

    while (particle.GetPosition().GetZ() > 0 && !stopThreads)
    {
        auto start = std::chrono::system_clock::now();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        particle.Integrate(0.2);

        std::cout << particle << std::endl;
    }

    return 0;
}

void updateUI() {


    return;
}

int main(int, char**)
{
    Vector3 initialPosition(0, 0, 0.01);
    Vector3 initialSpeed(0, 0, 100);
    Vector3 acceleration(0, 0, -9.81);

    Particle particle(initialPosition, initialSpeed, acceleration);

    // thread : https://www.cplusplus.com/reference/thread/thread/
    std::thread threadCalcul(updateObj, particle);     // spawn new thread that calls foo()
    std::thread threadUI(updateUI);     // spawn new thread that calls foo()

    // synchronize threads:
    threadCalcul.join();                // pauses until first finishes
    threadUI.join();               // pauses until second finishes

    stopThreads = true;

    return 0;
}
