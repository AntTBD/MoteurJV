#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Particle.h"
#include "Vector3.h"
#include "GUI.h"
#include "Simulator.h"

void UI()
{
    GUI gui;
    gui.init();
    gui.update();
    gui.end();

    return;
}

int main(int, char**)
{
    std::thread threadUI(UI);     // spawn new ui thread
    // synchronize threads:
    threadUI.join();               // pauses until second finishes

    return 0;
}
