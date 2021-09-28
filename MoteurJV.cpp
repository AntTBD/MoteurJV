#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Particle.h"
#include "Vector3.h"
#include "GUI.h"
#include "Simulator.h"

/// <summary>
/// Thread for 3D user interface face manager
/// </summary>
/// <param name="sim">Pointer gathering all the characteristics of the particles of the scene</param>
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
