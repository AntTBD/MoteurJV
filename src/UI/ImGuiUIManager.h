#ifndef ImGuiUIManager_H_
#define ImGuiUIManager_H_
#include "../ImGuiIncludes.h"
#include "../ClassIncludes.h"

// code extrait de imguix.x.x/example/example_glfw_opengl3

#include "MainWindow.h"
#include "ImGuiUIWindow.h"
#include "ImGuiUIWindowRegistry.h"
#include "ImGuiUIWindowConfig.h"
#include "ImGuiUIWindowRender.h"
#include "ImGuiUIWindowConsole.h"
#include "ImGuiUIWindowInspector.h"

#include <vector>

/// <summary>
/// User Interface Manager (ImGui + OpenGL)
/// </summary>
class ImGuiUIManager
{
public:
    ImGuiUIManager(MainWindow* mainWindow);
	~ImGuiUIManager();
	void update();
	void render();

    // find window by type
    // ex : FindWindow<MyClass>()
    template <class T>
    T* FindWindow();
private:
    ImGuiUIWindowRegistry* imGuiUIWindowRegistry;
	std::vector<ImGuiUIWindow*> windows;
	void ShowDockSpace(bool* p_open);
	void setStyle();
};

#endif // ImGuiUIManager_H_