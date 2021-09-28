#pragma once

// inspiration from http://www.songho.ca/opengl/gl_matrix.html#example1
// TODO : http://www.songho.ca/opengl/gl_camera.html#lookat

#include <math.h>

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

// Include GLM
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

/// <summary>
/// Orbital Camera
/// </summary>
class Camera
{
private:
	// ----- Position -----
	float camDist; // distance
	float rotationOnX; // height angle
	float rotationOnY; // rotation angle around the center

	// ----- Projection -----
	float fov; // field of view
	float nearF; // minimum viewing distance
	float far; // max viewing distance

public:
	Camera();
	Camera(float dist, float rotationX, float rotationY);
	~Camera();

	void AddOrbitalRotationY(float angleDelta);
	void Set(float dist, float rotationX, float rotationY);
	void Add(float dist, float rotationX, float rotationY);
	void Update();

	glm::mat4 SetProjection(float Translate, glm::vec2 const& Rotate);
};

