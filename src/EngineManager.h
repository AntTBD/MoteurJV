#pragma once

#include "UI/MainWindow.h"
#include "UI/ImGuiUIManager.h"
#include "3DScene/OpenGLRendererManager.h"

class EngineManager {
private:
    MainWindow* mainWindow;
    ImGuiUIManager* uiManager;
    OpenGLRendererManager* openGlRendererManager;
    bool running;
public:
    EngineManager();
    ~EngineManager();
    void run();
    void stop();
    bool isRunning();
    MainWindow* getMainWindow();
};
