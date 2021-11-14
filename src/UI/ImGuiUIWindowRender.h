#ifndef ImGuiUIWindowRender_H_
#define ImGuiUIWindowRender_H_
#include "../ClassIncludes.h"


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
    void checkToAddParticles();
};

#endif // ImGuiUIWindowRender_H_