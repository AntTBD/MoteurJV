#pragma once

#include "../ImGuiIncludes.h"

#include "../Math/Vector3.h"
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
    GLuint debugSphere;

public:
    Formes();

    void Init();

    void DrawCube();
    void DrawSphere();
    void DrawAxis();
    void DrawLine();
    void DrawTriangle();
    void DrawCarre();
    void DrawDebugSphere();

private:
    void CreateCube();
    void CreateSphere();
    void CreateAxis();
    void CreateLine();
    void CreateTriangle();
    void CreateCarre();
    void CreateDebugSphere();

};

