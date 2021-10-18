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



// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

// Include 3D manager and simulator
#include "OpenGL3.h"
#include "Simulator.h"
// include threads
#include <thread>
// include chrono
#include <chrono>

/// <summary>
/// User Interface Manager (ImGui + OpenGL + Simulator)
/// </summary>
class GUI
{
private:
	GLFWwindow* window;

	// Our state
	bool show_config_window;
	ImVec4 clear_color;

	OpenGL3* opengl;

	// Simulation
	bool isSimulating;
	bool isThreadActive;
	Simulator* sim;
	std::thread simThread;

public:
	GUI(Simulator* sim = nullptr); // Pointer to the particles simulator
	int init();
	void update();
	void end();
	void showConfigWindow();
	void render3D();

	// Used on the simulator when pressing buttons
	void Simulate(); 
	void Clear();
	void Pause(); // Pause or resume

};



