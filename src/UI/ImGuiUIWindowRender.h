#pragma once

#include "ImGuiUIWindow.h"
#include "../3DScene/Shader.h"
#include "../../Camera.h"

class ImGuiUIWindowRender : public ImGuiUIWindow {
private:
    GLuint textureColorbuffer, framebuffer;
    //Shader* shader;
    // Orbital camera
    Camera* cam;
    ImVec4 clear_color;

    // variables
    bool play, pause;
public:
    ImGuiUIWindowRender(bool show = true);
    ~ImGuiUIWindowRender();

    void update() override;
    void newSize(float width, float height);
    void render3D();
    void drawPlan(float nbrUnits, float scale);
    void drawAxis(float echelle);
};