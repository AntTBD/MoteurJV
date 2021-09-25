#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Particle.h"
#include "Vector3.h"
#include "GUI.h"
#include "Simulator.h"


std::atomic_bool stopThreads = false;

void updateUI()
{
    GUI gui;
    gui.init();
    gui.update();
    gui.end();

    return;
}

void updateObj()
{
    Simulator sim;
    Particle p1 = Particle(Vector3(0, 100, 0), Vector3(0, 0, 0), 1, 1);
    Particle p2 = Particle(Vector3(50, 200, 0), Vector3(0, 0, 0), 1, 2);
    p2.AddForce(Vector3(10, 0, 0));

    sim.AddParticle(p1);
    sim.AddParticle(p2);

    sim.Update();

    return;
}

void Stop()
{
    stopThreads = true;
}

int main(int, char**)
{
    // thread : https://www.cplusplus.com/reference/thread/thread/
    std::thread threadUI(updateUI);     // spawn new ui thread
    std::thread threadObj(updateObj);

    // synchronize threads:
    threadUI.join();               // pauses until second finishes
    threadObj.join();

    Stop();

    return 0;
}
