#include "Camera.h"

Camera::Camera()
{
	// ----- Position -----
	this->camDist = 10.0f; // distance
	this->rotationOnX = 45.0f; // angle en hauteur
	this->rotationOnY = -45.0f; // rotation angle autour du centre

	// ----- Projection -----
	this->fov = 90.0f;
	this->nearF = 0.2f;
	this->far = 100.0f;
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

void Camera::OrbitalRotationY(float angleDelta)
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

void Camera::Update()
{

	//glMatrixMode(GL_PROJECTION);// 2D Projection
	glMatrixMode(GL_MODELVIEW); // 3D Projection
	glLoadIdentity();

	//this->UpdateProjection();
	//this->UpdatePosition();
	// 
	// --------
	glLoadMatrixf(glm::value_ptr(this->SetProjection(camDist, glm::vec2(glm::radians(this->rotationOnY), glm::radians(this->rotationOnY)))));
	// --------



	//glMatrixMode(GL_MODELVIEW); // 3D Projection
	//glLoadIdentity();
}

void Camera::UpdateProjection()
{
	ImGuiIO& io = ImGui::GetIO();

	/*
	// https://opengl.developpez.com/tutoriels/opengl-tutorial/6-clavier-et-souris/
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rotationDegrees), glm::vec3(1.0f, 1.0f, 0.0f));
	glm::mat4 modelTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f));
	// Matrice de vue
	glm::mat4 view = glm::lookAt(
		glm::vec3(yY, xX, zZ), // La caméra est là
		glm::vec3(0.0f, 0.0f, 0.0f), // et regarde ici : à la même position, plus la « direction »
		glm::vec3(0.0f, 1.0f, 0.0f) // la tête est vers le haut (définir à 0,-1,0 pour voir à l'envers)
	);
	glm::mat4 modelview = view * modelTransform * rotation;
	*/

	// Matrice de projection : champ de vision 45°, ration 4:3, distance d'affiche : 0.1 unit <-> 100 units 
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), (float)io.DisplaySize.x / (float)io.DisplaySize.y, nearF, far);

	// https://github.com/ocornut/imgui/issues/2760#issuecomment-526557526
	glLoadMatrixf(glm::value_ptr(projectionMatrix));//3D projection

}

void Camera::UpdatePosition()
{
	//glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, nearF, far);// GL_PROJECTION 2D 
	//glOrtho(-1.0, 1.0, -1.0, 1.0, nearF, far);// Orthographic Projection
 //   glTranslatef(-xX, -yY, -zZ);
	//glRotatef(-25, 1, 0, 0);
 //   glRotatef(-rotationDegrees, 0, 1, 0);
	//glRotatef(-25, 0, 0, 1);
	glTranslatef(0, 0, -this->camDist);       // 3rd: translate along z
	glRotatef(-this->rotationOnX, 1, 0, 0);       // 2nd: rotate on x-axis
	glRotatef(this->rotationOnY, 0, 1, 0);       // 1st: rotate on y-axis
}

glm::mat4 Camera::SetProjection(float Translate, glm::vec2 const& Rotate)
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