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

    Vector3 vec = Vector3(0.0f, -1.0f, 0.0f);

    Quaternion testQuaternion(vec,0);
    
    //test.RotateByVector(vec);
    testQuaternion.RotateByVector(vec);
    std::cout<< testQuaternion << std::endl;







    //std::cout<< testQuaternion.EulerToQuaternion(vec) << std::endl;






    std::cout<< "--------------------------------" << std::endl;
  
    std::vector<float> values12 = { 1.0f, 2.0f, 3.0f, 10.0f, 4.0f, 5.0f, 6.0f, 10.0f, 7.0f, 8.0f, 9.0f, 10.0f };
    std::vector<float> values9 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    Matrix34 A = Matrix34(values12);
    Matrix33 B = Matrix33(values9);
    Vector3 vec2 = Vector3(2.0f, 4.0f, 7.0f);
    std::cout << A << std::endl;
    std::cout << B << std::endl;

    std::cout << A.TransformDirection(vec2) << std::endl;
    std::cout << B.TransformPosition(vec2) << std::endl;

    //std::cout << A.TransformPosition(vec2) << std::endl;
    
    //std::cout << A.TransformPosition(vec2) << std::endl;
    //std::cout << A.TransformDirection(vec2) << std::endl;
    
  
    // --------------------------------
    // Engine
    EngineManager::getInstance().run();

    return 0;
}
