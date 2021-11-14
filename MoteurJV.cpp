/*#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "src/Physic/Particle.h"
#include "src/Math/Vector3.h"
#include "GUI.h"
#include "Simulator.h"
#include "src/Math/Matrix33.h"
#include "src/Math/Matrix34.h"
#include "src/Math/Quaternion.h"*/

#include "src/EngineManager.h"
/*
/// <summary>
/// Thread for 3D user interface face manager
/// </summary>
/// <param name="sim">Pointer gathering all the characteristics of the particles of the scene</param>
int UI(Simulator* sim)
{
    //GUI gui(sim);
    //int gui_init = gui.init();
    //if(gui_init != 0)
    //    return gui_init;
    //gui.update();
    //gui.end();

    EngineManager::getInstance().run();

    return 0;
}*/

int main(int, char**)
{
    //Simulator sim;
    //std::thread threadUI(UI, &sim);     // spawn new ui thread

    /*float values[12] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
    Matrix34 A = Matrix34(values);
    Vector3 vec = Vector3(0.0f, 0.0f, 1.0f);
    
    std::cout << A.TransformPosition(vec) << std::endl;
    std::cout << A.TransformDirection(vec) << std::endl;
*/
    // synchronize threads:
    //threadUI.join();               // pauses until second finishes

    EngineManager::getInstance().run();
    return 0;
}
