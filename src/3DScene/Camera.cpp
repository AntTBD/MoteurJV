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
	this->nearF = 0.1f;
	this->m_far = 10000.0f;

    // ------ size ---------
    this->width = 10;
    this->height = 10;

    // --- background ----
    this->setBackground(0.1f, 0.1f, 0.1f, 1.0f); // dark

}

Camera::Camera(float dist, float rotationX, float rotationY)
{
	// ----- Position -----
	this->Set(dist, rotationX, rotationY);

	// ----- Projection -----
	this->fov = 90.0f;
	this->nearF = 0.1f;
    this->m_far = 10000.0f;

    // ------ size ---------
    this->width = 10;
    this->height = 10;

    // --- background ----
    this->setBackground(0.1f, 0.1f, 0.1f, 1.0f); // dark

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
    // make sure we clear the framebuffer's content
    glClearDepth( 1.0 );
    glClearColor(this->background.x, this->background.y, this->background.z, this->background.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); // 3D Projection
	glLoadIdentity();

    // resize cam size
    glViewport(0, 0, this->width, this->height);

	// --------
	glLoadMatrixf(glm::value_ptr(this->SetProjection(this->camDist, glm::vec2(glm::radians(this->rotationOnY), glm::radians(this->rotationOnX)))));
	// --------

}

float Camera::GetDistance() const
{
	return this->camDist;
}

void Camera::SetDistance(float distFromCenter)
{
	if (distFromCenter < 0) distFromCenter = 0; // distance mini = 0
	this->camDist = distFromCenter;
}

void Camera::setSize(float width, float height) {
    this->width = width;
    this->height = height;
}

ImVec2 Camera::getSize() const {
    return {this->width, this->height};
}

float Camera::getWidth() const {
    return this->width;
}
float Camera::getHeight() const {
    return this->height;
}

ImVec4 Camera::getBackground() {
    return this->background;
}

void Camera::setBackground(float r, float g, float b, float a) {
    this->background = ImVec4(r, g, b, a);
}

glm::mat4 Camera::SetProjection(float Translate, glm::vec2 const& Rotate)
{
	// from https://github.com/g-truc/glm (perspective var changed to use ours)
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)this->width / (float)this->height, this->nearF, this->m_far);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
}
