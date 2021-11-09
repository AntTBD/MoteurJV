#pragma once

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

#include <string>

// generic class for ImGui Windows
class ImGuiUIWindow
{
public:
    ImGuiUIWindow(bool show = true);
	~ImGuiUIWindow();
    virtual void update();

protected:

	bool begin(std::string name);
	void end();

    bool needShow();
    void show();
    void hide();
    void toggle();

private:
    bool _show;
};