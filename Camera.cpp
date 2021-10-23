#include "Camera.h"
#include <iostream>

Camera::Camera()
{
	// ----- Position -----
	this->camDist = 10.0f; // distance
	this->rotationOnX = 45.0f; // angle en hauteur
	this->rotationOnY = -45.0f; // rotation angle autour du centre

	// ----- Projection -----
	this->fov = 90.0f;
	this->nearF = 0.2f;
	this->far = 10000.0f;
}

Camera::Camera(float dist, float rotationX, float rotationY)
{
	// ----- Position -----
	this->Set(dist, rotationX, rotationY);

	// ----- Projection -----
	this->fov = 90.0f;
	this->nearF = 0.2f;
	this->far = 100.0f;
}

Camera::~Camera()
{
}

void Camera::AddOrbitalRotationY(float angleDelta)
{
	this->rotationOnY += angleDelta;
	if (this->rotationOnY >= 360 || this->rotationOnY <= -360) {
		this->rotationOnY = fmod(this->rotationOnY, 360.0f); // fmod from math.h
	}
}

void Camera::Set(float dist, float rotationX, float rotationY)
{
	this->camDist = dist; // distance

	this->rotationOnX = rotationX; // angle en hauteur
	this->rotationOnY = rotationY; // rotation angle autour du centre
}

void Camera::Add(float dist, float rotationX, float rotationY)
{
	this->camDist += dist; // distance

	this->rotationOnX += rotationX; // angle en hauteur
	this->rotationOnY += rotationY; // rotation angle autour du centre
}

void Camera::Update()
{
	glMatrixMode(GL_MODELVIEW); // 3D Projection
	glLoadIdentity();

	// --------
	glLoadMatrixf(glm::value_ptr(this->SetProjection(this->camDist, glm::vec2(glm::radians(this->rotationOnY), glm::radians(this->rotationOnX)))));
	// --------

}

float Camera::GetDistance()
{
	return this->camDist;
}

void Camera::SetDistance(float distFromCenter)
{
	if (distFromCenter < 0) distFromCenter = 0; // distance mini = 0
	this->camDist = distFromCenter;
}

glm::mat4 Camera::SetProjection(float Translate, glm::vec2 const& Rotate)
{
	// from https://github.com/g-truc/glm (perspective var changed to use ours)
	ImGuiIO& io = ImGui::GetIO();
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)io.DisplaySize.x / (float)io.DisplaySize.y, this->nearF, this->far);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}