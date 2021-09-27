#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// Include GLM
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
//using namespace glm;

#include "Simulator.h"
#include "Camera.h"

class OpenGL3
{
public:
	OpenGL3(Simulator* sim = nullptr);
	void update();


	void createTriangle();

	void drawAxis(float echelle = 1);
	void drawPlan(float nbrUnits = 1);
	void drawRect2D(double largeur, double hauteur);
	void drawCube(double largeur, double hauteur);
	void DrawAllParticules();

private:
	Simulator* sim;

	Camera* cam;
	float rotationCamDeltaY;
};

