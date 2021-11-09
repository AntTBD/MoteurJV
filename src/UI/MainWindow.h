#pragma once


// Include GLFW
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers


class MainWindow {
private:
    GLFWwindow* window;
    int width;
    int height;
    const char* title;

public:
    MainWindow(int width, int height, const char* title = NULL);
    ~MainWindow();

    void render();

    int getWidth();
    int getHeight();
    void setSize(int width, int height);

    const char* getTitle();
    void setTitle(const char* title);

    GLFWwindow* getWindow();
    void setWindow(GLFWwindow* window);
};
