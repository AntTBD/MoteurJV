#pragma once

#include <imgui_impl_glfw.h>

// Include GLFW
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers


class Mouse
{
public:
	float x, y;
	int entered; // to now if mouse on window
	int button;
	int action;
	double scrollX, scrollY;
	bool buttonChange;


	Mouse();

	void SetPosition(double xpos, double ypos);
	void SetEnter(int _entered);
	void SetButton(int _button, int _action, int _mods);
	void SetScroll(double xoffset, double yoffset);

	bool ButtonHasChange();

	/*void Init(GLFWwindow* window);

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	static void cursor_enter_callback(GLFWwindow* window, int _entered);

	static void mouse_button_callback(GLFWwindow* window, int _button, int _action, int _mods);

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);*/
};

