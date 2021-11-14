#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Particle.h"
#include "Vector3.h"
#include "GUI.h"
#include "Simulator.h"
#include "Matrix33.h"
#include "Matrix34.h"
#include "Quaternion.h"

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
    //Simulator sim;
    //std::thread threadUI(UI, &sim);     // spawn new ui thread

    float values[12] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
    Matrix34 A = Matrix34(values);
    Vector3 vec = Vector3(0.0f, 0.0f, 1.0f);
    
    std::cout << A.TransformPosition(vec) << std::endl;
    std::cout << A.TransformDirection(vec) << std::endl;

    // synchronize threads:
    //threadUI.join();               // pauses until second finishes

    return 0;
}
