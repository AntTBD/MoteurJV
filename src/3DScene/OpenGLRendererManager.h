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

// Include GLM
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


#include "../UI/MainWindow.h"
#include "../IO/InputManager.h"


class OpenGLRendererManager {
private:
    MainWindow* mainWindow;
    unsigned int textureColorbuffer;
    InputManager* inputManager;
public:
    ImVec4 clear_color;
    OpenGLRendererManager(MainWindow* mainWindow);
    ~OpenGLRendererManager();

    void preRender();
    void render();
    void postRender();

    GLFWwindow* getWindow();
    void setNewWindowSize(int width, int height);
    unsigned int getFrame();

    bool windowShouldClose();
    void framebufferSizeCallback(int width, int height);
    void processInput(GLFWwindow *window);
    void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
};
