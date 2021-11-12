#include "EngineManager.h"


EngineManager::EngineManager()
{
    this->mainWindow = new MainWindow(1280, 720, "Moteur physique de Jeux Video");
    this->openGlRendererManager = new OpenGLRendererManager(this->mainWindow);
    this->uiManager = new ImGuiUIManager(this->mainWindow);
    this->running = true;

    // add input manager
    this->inputManager = new InputManager();
}

EngineManager::~EngineManager()
{
    delete this->mainWindow;
    delete this->uiManager;
    delete this->openGlRendererManager;
    delete this->inputManager;
}

void EngineManager::run()
{
    while (this->isRunning())
    {
        // check inputs
        this->inputManager->update(this->mainWindow);

        this->openGlRendererManager->render(); // clear + render 3D
        this->uiManager->update();// add windows to imgui
        this->uiManager->render();// render all imgui windows
        this->mainWindow->render();// swap buffers of the window
    }
}

void EngineManager::stop()
{
    this->running = false;
}

bool EngineManager::isRunning()
{
    if(glfwWindowShouldClose(this->mainWindow->getWindow()))
        this->stop();// stop

    return this->running;
}

MainWindow* EngineManager::getMainWindow()
{
    return this->mainWindow;
}