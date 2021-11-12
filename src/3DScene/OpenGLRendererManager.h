#pragma once

#include "../myIncludes.h"

#include "../UI/MainWindow.h"
#include "Shader.h"


class OpenGLRendererManager {
private:
    MainWindow* mainWindow;
    GLuint VBO, VAO, EBO, textureColorbuffer;
    Shader* shader;
    ImVec4 clear_color;
public:
    OpenGLRendererManager(MainWindow* mainWindow);
    ~OpenGLRendererManager();

    void render();
    void postRender();

    GLFWwindow* getWindow();
    void setNewWindowSize(int width, int height);
    GLuint getFrame();

    bool windowShouldClose();
    void framebufferSizeCallback(int width, int height);
    void processInput(GLFWwindow *window);
    void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
};
