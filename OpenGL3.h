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

// Include global simulator and camera
#include "Simulator.h"
#include "Camera.h"

/// <summary>
/// 3D OpenGL Manager
/// </summary>
class OpenGL3
{
private:
	Simulator* sim;

	// Orbital camera
	Camera* cam;
	// rotaion angle
	float rotationCamDeltaY;

public:
	OpenGL3(Simulator* sim = nullptr);

	void update();

	void createTriangle();

	void drawAxis(float echelle = 1);
	void drawPlan(float nbrUnits = 1);

	void drawRect2D(double largeur, double hauteur);
	void drawCube(double largeur, double hauteur);

	void DrawAllParticules();

};

