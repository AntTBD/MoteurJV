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
    //EngineManager::getInstance().run();

    float values12[12] = { 1.0f, 2.0f, 3.0f, 10.0f, 4.0f, 5.0f, 6.0f, 10.0f, 7.0f, 8.0f, 9.0f, 10.0f };
    float values9[9] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    Matrix34 A = Matrix34(values12);
    Matrix33 B = Matrix33(values9);
    Vector3 vec = Vector3(2.0f, 4.0f, 7.0f);
    std::cout << A << std::endl;
    std::cout << B << std::endl;

    std::cout << A.TransformDirection(vec) << std::endl;
    std::cout << B.TransformPosition(vec) << std::endl;


    return 0;
}
