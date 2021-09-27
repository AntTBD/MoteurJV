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


class OpenGL3
{
public:
	OpenGL3();
	void create3dModels();


	void createTriangle();

	void drawAxis(float echelle = 1);
	void drawPlan(float nbrUnits = 1);
	void drawRect2D(double largeur, double hauteur);
	void drawCube(double largeur, double hauteur);


	GLuint* textureSceneRendered;

	glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
	{
		// https://github.com/g-truc/glm
		ImGuiIO& io = ImGui::GetIO();
		glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)io.DisplaySize.x / (float)io.DisplaySize.y, this->nearF, this->far);
		glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
		View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
		View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
		return Projection * View * Model;
	}

	float rotationDegrees = 0.0f;
	float fov = 150.0f; // champ de vision
	float nearF = 0.2f; // distance de vision minimal
	float far = 100.0f; // distance max de vision
	float xX = 0.0f;
	float yY = 5.0f;
	float zZ = 5.0f;
	float camDist = 10.0f;
};

