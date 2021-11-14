#include "EngineManager.h"


EngineManager::EngineManager()
{
    // window
    this->mainWindow = new MainWindow(1280, 720, "Moteur physique de Jeux Video");
    // render
    this->openGlRendererManager = new OpenGLRendererManager(this->mainWindow);
    // ui
    this->uiManager = new ImGuiUIManager(this->mainWindow);
    this->running = true;

    // add input manager
    this->inputManager = new InputManager();
    // scene
    this->scene = new Scene();

    // physicEngine
    this->physicEngine = new PhysicEngine();


}

EngineManager::~EngineManager()
{
    delete this->mainWindow;
    delete this->uiManager;
    delete this->openGlRendererManager;
    delete this->inputManager;
    delete this->scene;
}

void EngineManager::run()
{
    while (this->isRunning())
    {
        // check inputs
        this->inputManager->update(this->mainWindow);
        // update logic
        // this->physicEngine start Simulation when we press on start (start thread)

        // update outputs screen
        this->openGlRendererManager->render(); // clear + render 3D
        this->uiManager->update();// add windows to imgui
        this->uiManager->render();// render all imgui windows
        this->mainWindow->render();// swap buffers of the window
    }
}

void EngineManager::close()
{
    this->running = false;
}

bool EngineManager::isRunning()
{
    if(this->openGlRendererManager->windowShouldClose())
        this->close();// close mainWindow

    return this->running;
}

MainWindow* EngineManager::getMainWindow()
{
    return this->mainWindow;
}

Scene *EngineManager::getScene() {
    return this->scene;
}

PhysicEngine *EngineManager::getPhysicEngine() {
    return this->physicEngine;
}

ImGuiUIManager* EngineManager::getUiManager(){
    return this->uiManager;
}