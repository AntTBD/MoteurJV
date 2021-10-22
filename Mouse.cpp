#include "Mouse.h"
#include <iostream>

Mouse::Mouse() {

	x=y=0.0f;
	entered=-1; // to now if mouse on window
	button=-1;
	action=-1;
	scrollX= scrollY = 0.0;
	buttonChange = false;
}

void Mouse::SetPosition(double xpos, double ypos) {
	if (entered)
	{
		// The cursor entered the content area of the window
		x = xpos;
		y = ypos;
	}
	else
	{
		// The cursor left the content area of the window
	}
}

void Mouse::SetEnter(int _entered)
{
	entered = _entered;
}

void Mouse::SetButton(int _button, int _action, int _mods)
{
	buttonChange = true;
	button = _button;//GLFW_MOUSE_BUTTON_RIGHT;
	action = _action;//GLFW_PRESS;
}

void Mouse::SetScroll(double xoffset, double yoffset)
{
	scrollX = xoffset;
	scrollY = yoffset;
}

bool Mouse::ButtonHasChange() {
	if (buttonChange) {
		buttonChange = false;
		return true;
	}
	else
		return false;
}

/*
void Mouse::Init(GLFWwindow* window)
{
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetCursorEnterCallback(window, cursor_enter_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
}

void Mouse::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

}

void Mouse::cursor_enter_callback(GLFWwindow* window, int _entered)
{
	_instance->entered = _entered;
}

void Mouse::mouse_button_callback(GLFWwindow* window, int _button, int _action, int _mods)
{
	_instance->button = _button;//GLFW_MOUSE_BUTTON_RIGHT;
	_instance->action = _action;//GLFW_PRESS;
}

void Mouse::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	_instance->scrollX = xoffset;
	_instance->scrollY = yoffset;
}*/