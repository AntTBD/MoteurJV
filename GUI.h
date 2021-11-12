#pragma once

// code extrait de imguix.x.x/example/example_glfw_opengl3
#include "includesUI.h"

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
	bool IsMouseOnWidgets();
	void render3D();

	// Used on the simulator when pressing buttons
	void Simulate(); 
	void Clear();
	void Pause(); // Pause or resume
};



