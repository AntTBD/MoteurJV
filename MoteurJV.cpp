#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Particle.h"
#include "Vector3.h"
#include "GUI.h"
#include "Simulator.h"

void UI(Simulator* sim)
{
    GUI gui(sim);
    gui.init();
    gui.update();
    gui.end();

    return;
}

int main(int, char**)
{
    Simulator sim;
    std::thread threadUI(UI, &sim);     // spawn new ui thread

    // synchronize threads:
    threadUI.join();               // pauses until second finishes

    return 0;
}
