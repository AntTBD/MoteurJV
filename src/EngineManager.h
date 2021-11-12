#pragma once

class ImGuiUIManager;

#include "UI/MainWindow.h"
#include "UI/ImGuiUIManager.h"
#include "IO/InputManager.h"
#include "3DScene/OpenGLRendererManager.h"
#include "Scene.h"

class EngineManager {
private:
    MainWindow* mainWindow;
    ImGuiUIManager* uiManager;
    OpenGLRendererManager* openGlRendererManager;
    InputManager* inputManager;
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
    void run();
    void close();
    bool isRunning();
    MainWindow* getMainWindow();
    Scene* getScene();
};
