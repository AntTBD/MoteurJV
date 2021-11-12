#pragma once

#include "ImGuiUIWindow.h"
#include "../EngineManager.h"

class ImGuiUIWindowConfig : public ImGuiUIWindow {
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
    ImGuiUIWindowConfig(bool show = true);
    ~ImGuiUIWindowConfig();

    void update() override;
};