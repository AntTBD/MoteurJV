#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "src/Physic/Particle.h"
#include "src/Math/Vector3.h"
#include "src/Math/Matrix33.h"
#include "src/Math/Matrix34.h"
#include "src/Math/Quaternion.h"

#include "src/EngineManager.h"

int main(int, char**)
{
    // Engine
    EngineManager::getInstance().run();

    float values[12] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
    Matrix34 A = Matrix34(values);
    Vector3 vec = Vector3(0.0f, 0.0f, 1.0f);
    
    std::cout << A.TransformPosition(vec) << std::endl;
    std::cout << A.TransformDirection(vec) << std::endl;


    return 0;
}
