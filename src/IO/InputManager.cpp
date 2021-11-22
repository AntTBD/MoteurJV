#include "InputManager.h"

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

void InputManager::update(MainWindow* mainWindow)
{
    if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(mainWindow->getWindow(), true);

    // blob
    static bool b_key_pressed = false;
    if(EngineManager::getInstance().getPhysicEngine()->isRunning() == false && b_key_pressed == false && glfwGetKey(mainWindow->getWindow(), GLFW_KEY_B) == GLFW_PRESS){
        b_key_pressed = true;
        Blob::GenerateScene();
    }
    if(b_key_pressed && glfwGetKey(mainWindow->getWindow(), GLFW_KEY_B) == GLFW_RELEASE){
        b_key_pressed = false;
    }

    // rigidbody rotation
    static bool r_key_pressed = false;
    if(EngineManager::getInstance().getPhysicEngine()->isRunning() == false && r_key_pressed == false && glfwGetKey(mainWindow->getWindow(), GLFW_KEY_R) == GLFW_PRESS){
        r_key_pressed = true;
        RigidBodyRotation::GenerateScene();
    }
    if(r_key_pressed && glfwGetKey(mainWindow->getWindow(), GLFW_KEY_R) == GLFW_RELEASE){
        r_key_pressed = false;
    }

    // car Collision
    static bool c_key_pressed = false;
    if(EngineManager::getInstance().getPhysicEngine()->isRunning() == false && c_key_pressed == false && glfwGetKey(mainWindow->getWindow(), GLFW_KEY_C) == GLFW_PRESS){
        c_key_pressed = true;
        CarCollision::GenerateScene();
    }
    if(c_key_pressed && glfwGetKey(mainWindow->getWindow(), GLFW_KEY_C) == GLFW_RELEASE){
        c_key_pressed = false;
    }
}