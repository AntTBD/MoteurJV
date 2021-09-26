#pragma once
// code extrait de example/example_glfw_opengl3

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include "OpenGL3.h"

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "Simulator.h"
#include <thread>

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

class GUI
{
public:
	GUI();
	int init();
	void update();
	void end();
	void showConfigWindow();
	void render3D();
	void Simulate();
	void Clear();

private:
	GLFWwindow* window;

	// Our state
	bool show_demo_window;
	bool show_another_window;
	bool show_config_window;
	ImVec4 clear_color;

	OpenGL3* opengl;

	// simulation
	bool isSimulating;
	bool isThreadActive;
	Simulator sim;
	std::thread simThread;
};



