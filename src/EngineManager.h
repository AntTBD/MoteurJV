#ifndef EngineManager_H_
#define EngineManager_H_
#include "ClassIncludes.h"
#include "Debug/Debug.h"


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
    AppLog console;
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
    ImGuiUIManager* getUiManager();
    bool isRunning();
    void run();
};


#endif // EngineManager_H_