#ifndef OpenGLRendererManager_H_
#define OpenGLRendererManager_H_
#include "../ImGuiIncludes.h"
#include "../ClassIncludes.h"

#include "../UI/MainWindow.h"
#include "Shader.h"
#include "Formes.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix34.h"


class OpenGLRendererManager {
private:
    MainWindow* mainWindow;
    GLuint VBO, VAO, EBO, textureColorbuffer;
    Shader* shader;
    ImVec4 clear_color;
public:
    static Formes* formes;// declared at the beginning of .cpp

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

    // Create multicolor 2D triangle with glVertex
    static void drawTriangle();
    // Create axis for 3 dimensions
    static void drawPlan(float nbrUnits, float scale);
    // Create plan for nbrUnits positifs
    static void drawAxis(float echelle);
    // Create 2D rectangle with the middle of the left side as a reference point
    static void drawRect2D(double largeur, double hauteur);
    // Create 3D parallelepiped with the center as a reference point
    static void drawCube(const Vector3& dimensions = Vector3(1.f,1.f,1.f), const Vector3& pos = Vector3(0,0,0), const Matrix34& transformMatrix = Matrix34(), const Vector3& rot = Vector3(0,0,0));
    // Create 3D sphere with the center as a reference point (with specific diametre)
    static void drawSphere(const Vector3& dimensions = Vector3(1.f,1.f,1.f), const Vector3& pos = Vector3(0,0,0), const Matrix34& transformMatrix = Matrix34(), const Vector3& rot = Vector3(0,0,0));


};

#endif // OpenGLRendererManager_H_
