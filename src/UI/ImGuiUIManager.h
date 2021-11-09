#pragma once
// code extrait de imguix.x.x/example/example_glfw_opengl3

// Include ImGui with OpenGL and GLFW
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

// Include GLFW
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers




#include "Window.h"

#include "ImGuiWindow.h"

/// <summary>
/// User Interface Manager (ImGui + OpenGL)
/// </summary>
class ImGuiUIManager
{
public:
    ImGuiUIManager(GLFWwindow* window, const char* glsl_version);
	~ImGuiUIManager();
	void update();
	void render();
	void addWindow(ImGuiWindow newWin);
private:
    GLFWwindow* window;
	std::vector<ImGuiWindow*> windows;
	void ShowDockSpace(bool* p_open);
	void setStyle();

	void showWindows();
	void deleteWindows();
};