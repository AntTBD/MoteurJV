#include <iostream>
#include <chrono>
#include <thread>
#include "Particle.h"
#include "Vector3.h"
#include "GUI.h"

std::atomic_bool stopThreads = false;

void updateObj(Particle particle)
{

    while (particle.GetPosition().GetY() > 0 && !stopThreads)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        particle.Integrate(0.2);

        std::cout << particle << std::endl;
    }

    return;
}

void updateUI()
{

    GUI gui;
    gui.init();
    gui.update();
    gui.end();


    return;
}

void Stop()
{
    stopThreads = true;
}

int main(int, char**)
{
    Vector3 initialPosition(0, 500, 0);
    Vector3 initialSpeed(0, 0, 0);

    Particle particle(initialPosition, initialSpeed, 1, 1);
    particle.AddForce(Vector3(20, 0, 0));

    // thread : https://www.cplusplus.com/reference/thread/thread/
    std::thread threadCalcul(updateObj, particle);     // spawn new thread that calls foo()
    std::thread threadUI(updateUI);     // spawn new thread that calls foo()

    // synchronize threads:
    threadCalcul.join();                // pauses until first finishes
    threadUI.join();               // pauses until second finishes

    Stop();

    return 0;
}
