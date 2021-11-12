#pragma once

#ifndef ENGINEMANAGER_H
#define ENGINEMANAGER_H

class ImGuiUIManager;
class PhysicEngine;

#include "UI/MainWindow.h"
#include "UI/ImGuiUIManager.h"
#include "IO/InputManager.h"
#include "3DScene/OpenGLRendererManager.h"
#include "Scene.h"
#include "Physics/PhysicEngine.h"

class EngineManager {
private:
    MainWindow* mainWindow;
    ImGuiUIManager* uiManager;
    OpenGLRendererManager* openGlRendererManager;
    InputManager* inputManager;
    PhysicEngine* physicEngine;
    bool running;
    Scene* scene;
public:
    static EngineManager& getInstance()
    {
        static EngineManager engineManagerInstance;
        return engineManagerInstance;
    }
    EngineManager();
    ~EngineManager();
    void close();
    MainWindow* getMainWindow();
    Scene* getScene();
    PhysicEngine* getPhysicEngine();
    bool isRunning();
    void run();
};

#endif // ENGINEMANAGER_H