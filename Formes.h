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

#include "Vector3.h"
// get pi
#define _USE_MATH_DEFINES
#include <math.h>

class Formes
{
private:
	GLuint cube;
    GLuint sphere;
    GLuint axes;
    GLuint line;
    GLuint triangle;
    GLuint carre;

public:
    Formes();

    void Init();

    void DrawCube();
    void DrawSphere();
    void DrawAxis();
    void DrawLine();
    void DrawTriangle();
    void DrawCarre();

private:
    void CreateCube();
    void CreateSphere();
    void CreateAxis();
    void CreateLine();
    void CreateTriangle();
    void CreateCarre();

};

