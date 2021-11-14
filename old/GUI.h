#pragma once

// code extrait de imguix.x.x/example/example_glfw_opengl3
#include "../src/ImGuiIncludes.h"

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}


// Vertex Shader source code
static const char* vertexShaderSourceCustom = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "uniform float size;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(size * aPos.x, size * aPos.y, size * aPos.z, 1.0);\n"
                                 "}\0";
//Fragment Shader source code
static const char* fragmentShaderSourceCustom = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "uniform vec4 color;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = color;\n"
                                   "}\n\0";



// Include 3D manager and simulator
#include "OpenGL3.h"
#include "Simulator.h"
// include threads
#include <thread>
// include chrono
#include <chrono>
#include <iostream>


/// <summary>
/// User Interface Manager (ImGui + OpenGL + Simulator)
/// </summary>
class GUI
{
private:
	GLFWwindow* window;

	// Our state
	bool show_config_window;
	bool show_render_window;
	ImVec4 clear_color;

	OpenGL3* opengl;

	// Simulation
	bool isSimulating;
	bool isThreadActive;
	Simulator* sim;
	std::thread simThread;


    /*//////////////////////////////////
    GLuint vertexShader, fragmentShader, shaderProgram;
    // Vertices coordinates
    GLfloat vertices[9] =
            {
                    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
                    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
                    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
            };

    // Create reference containers for the Vartex Array Object and the Vertex Buffer Object
    GLuint VAO, VBO;

    // Variables to be changed in the ImGUI window
    bool drawTriangle = true;
    float size = 1.0f;
    float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };
    /////////////////////////*/
public:


	GUI(Simulator* sim = nullptr); // Pointer to the particles simulator
	int init();
	void update();
	void end();
	void showRenderWindow();
	void showConfigWindow();
	bool IsMouseOnWidgets();
	void render3D();

	// Used on the simulator when pressing buttons
	void Simulate(); 
	void Clear();
	void Pause(); // Pause or resume
};



