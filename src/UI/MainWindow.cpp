#include "MainWindow.h"

MainWindow::MainWindow(int width, int height, const char* title) :
    width(width),
    height(height),
    title(title)
{}

MainWindow::~MainWindow()
{}

void MainWindow::render()
{
    int display_w, display_h;
    glfwGetFramebufferSize(this->window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    // swap buffers (invert front <-> back buffer)
    glfwSwapBuffers(this->window);

    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();
}

int MainWindow::getWidth()
{
    return this->width;
}

int MainWindow::getHeight()
{
    return this->height;
}

void MainWindow::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

const char* MainWindow::getTitle()
{
    return this->title;
}

void MainWindow::setTitle(const char* title)
{
    this->title = title;
}

GLFWwindow* MainWindow::getWindow()
{
    return this->window;
}

void MainWindow::setWindow(GLFWwindow* window)
{
    this->window = window;
}