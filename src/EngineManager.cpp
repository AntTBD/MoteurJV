#include "EngineManager.h"


EngineManager::EngineManager()
{
    this->mainWindow = new MainWindow(1280, 720, "Moteur physique de Jeux Video");
    this->openGlRendererManager = new OpenGLRendererManager(this->mainWindow);
    this->uiManager = new ImGuiUIManager(this->mainWindow);
    this->running = true;
}

EngineManager::~EngineManager()
{
    delete this->mainWindow;
    delete this->uiManager;
    delete this->openGlRendererManager;
}

void EngineManager::run()
{
    while (this->isRunning())
    {
        this->uiManager->update();// add windows to imgui
        this->openGlRendererManager->render(); // clear + render 3D
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
    return this->running;
}

MainWindow* EngineManager::getMainWindow()
{
    return this->mainWindow;
}