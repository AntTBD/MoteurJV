#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Physic/Particle.h"
#include "Math/Vector3.h"
#include "Math/Matrix33.h"
#include "Math/Matrix34.h"
#include "Math/Quaternion.h"

#include "EngineManager.h"

int main(int, char**)
{
    // Engine
    EngineManager::getInstance().run();

    float values[12] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
    Matrix34 A = Matrix34(values);
    Vector3 vec = Vector3(0.0f, 0.0f, 1.0f);
    
    Quaternion test = Quaternion(1.0f, 1.0f, 1.0f, 0.0f);

    std::cout<<test.RotateByVector(vec) << std::endl;

    //std::cout << A.TransformPosition(vec) << std::endl;
    
    //std::cout << A.TransformPosition(vec) << std::endl;
    //std::cout << A.TransformDirection(vec) << std::endl;
    

    return 0;
}
