#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Particle.h"
#include "Vector3.h"
#include "GUI.h"
#include "Simulator.h"
//#include "Quaternion.h"

#include "src/EngineManager.h"

/// <summary>
/// Thread for 3D user interface face manager
/// </summary>
/// <param name="sim">Pointer gathering all the characteristics of the particles of the scene</param>
void UI(Simulator* sim)
{
    /*GUI gui(sim);
    gui.init();
    gui.update();
    gui.end();*/

    EngineManager* engine = new EngineManager();
    engine->run();

    return;
}

int main(int, char**)
{
    Simulator sim;
    std::thread threadUI(UI, &sim);     // spawn new ui thread

    //Quaternion q = Quaternion(1, 2, 3, 4);
    //std::cout << q.GetW() << ", " << q.GetI() << ", " << q.GetJ() << ", " << q.GetK() << std::endl;
    //float val[] = { 5,6,7,8 };
    //Quaternion q2 = Quaternion(val);
    //std::cout << q2.GetW() << ", " << q2.GetI() << ", " << q2.GetJ() << ", " << q2.GetK() << std::endl;

    // synchronize threads:
    threadUI.join();               // pauses until second finishes

    return 0;
}
