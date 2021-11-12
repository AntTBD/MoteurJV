#pragma once


#include "ImGuiUIWindow.h"
#include "../3DScene/Shader.h"
#include "../3DScene/OpenGLRendererManager.h"
#include "../EngineManager.h"

class ImGuiUIWindowRender : public ImGuiUIWindow {
private:
    GLuint textureColorbuffer, framebuffer;
    //Shader* shader;

    // variables
    bool play, pause;
public:
    ImGuiUIWindowRender(bool show = true);
    ~ImGuiUIWindowRender();

    void update() override;
    void newSize(float width, float height);
    void render3D();
};