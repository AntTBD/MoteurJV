#pragma once



#include "../src/ImGuiIncludes.h"

// Include global simulator and camera
#include "Simulator.h"
#include "../src/3DScene/Camera.h"
#include "../src/3DScene/Formes.h"
#include "ReadFile.h"

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

	Formes* formes;
public:
	OpenGL3(Simulator* sim = nullptr);

	void InitFormes();

	void update();

	void createTriangle();

	void drawAxis(float echelle = 1.0f);
	void drawPlan(float nbrUnits = 1.0f, float scale = 1.0f);

	void drawRect2D(double largeur, double hauteur);
	void drawCube(double largeur, double hauteur);
	void DrawSphere(double diametre = 1.0);

	void DrawAllParticules();

	GLuint LoadShader(const char* vertex_path, const char* fragment_path);
};

