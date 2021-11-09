#pragma once

class ImGuiWindowConfig: public ImGuiWindow
{
private:
	// Variable needed to make a particle
	float px = 0.0f;
	float py = 5.0f;
	float pz = 0.0f;
	float sx = 0.0f;
	float sy = 0.0f;
	float sz = 0.0f;
	float mass = 10.0f;
public:
    void show() override;
};