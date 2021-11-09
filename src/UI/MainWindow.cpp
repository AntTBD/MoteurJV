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

    glfwSwapBuffers(this->window);
    //glfwPollEvents(); // look at OpenGLRendererManager::render()
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