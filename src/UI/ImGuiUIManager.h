#pragma once
// code extrait de imguix.x.x/example/example_glfw_opengl3

#include "../myIncludes.h"



#include "MainWindow.h"
#include "ImGuiUIWindow.h"
#include "ImGuiUIWindowRegistry.h"
#include "ImGuiUIWindowConfig.h"
#include "ImGuiUIWindowRender.h"

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
private:
    ImGuiUIWindowRegistry* imGuiUIWindowRegistry;
	std::vector<ImGuiUIWindow*> windows;
	void ShowDockSpace(bool* p_open);
	void setStyle();
};