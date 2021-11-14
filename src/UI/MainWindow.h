#ifndef MainWindow_H_
#define MainWindow_H_
#include "../ImGuiIncludes.h"
#include "../ClassIncludes.h"


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

#endif // MainWindow_H_