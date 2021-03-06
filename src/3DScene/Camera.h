#pragma once

// inspiration from http://www.songho.ca/opengl/gl_matrix.html#example1
// TODO : http://www.songho.ca/opengl/gl_camera.html#lookat

#include <math.h>

#include "../ImGuiIncludes.h"

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
	float m_far; // max viewing distance

    // ----- Size -------
    float width, height;

    // background
    ImVec4 background;

public:
	Camera();
	Camera(float dist, float rotationX, float rotationY);
	~Camera();

	void AddOrbitalRotationY(float angleDelta);
	void Set(float dist, float rotationX, float rotationY);
	void Add(float dist, float rotationX, float rotationY);

    // =======================
    // Clear background
    // 3D projection
    // Set viewport
    // Load projection matrix
    // =======================
	void Update();

	float GetDistance() const;
	void SetDistance(float distFromCenter);

    void setSize(float width, float height);
    ImVec2 getSize() const;
    float getWidth() const;
    float getHeight() const;

    // color between 0-1
    void setBackground(float r, float g, float b, float a);
    ImVec4 getBackground();

	glm::mat4 SetProjection(float Translate, glm::vec2 const& Rotate);
};

