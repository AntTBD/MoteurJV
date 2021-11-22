#include "OpenGLRendererManager.h"

Formes* OpenGLRendererManager::formes = new Formes();

// GLFW Callback error print messages as std error
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

OpenGLRendererManager::OpenGLRendererManager(MainWindow* mainWindow) :
    mainWindow(mainWindow)
{
    // set clear color
    //this->clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);               // bleuté
    this->clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);      // grisé


    // glfw: initialize and configure
    // ------------------------------

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return;
    }
    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    //const char* glsl_version = "#version 100"; // look at ImGuiUIManager
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    //const char* glsl_version = "#version 150"; // look at ImGuiUIManager
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    //const char* glsl_version = "#version 130"; // look at ImGuiUIManager
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // glfw main window creation (windowed)
    // ------------------------------------
    this->mainWindow->setWindow(glfwCreateWindow(this->mainWindow->getWidth(), this->mainWindow->getHeight(),  this->mainWindow->getTitle(), NULL, NULL));
    if (!this->getWindow()) {
        fprintf(stderr, "Failed to create window with graphics context\n");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(this->getWindow());
    glfwSwapInterval(1); // Enable vsync

    if (gladLoadGL() == 0)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return;
    }
    // configure global opengl state to be used with 3D view mode
    glEnable(GL_DEPTH_TEST);

    // init objects list callback
    //OpenGLRendererManager::formes = new Formes();
    OpenGLRendererManager::formes->Init();
}

OpenGLRendererManager::~OpenGLRendererManager()
{
    /// TODO: delete buffers

    // destroy main window
    glfwDestroyWindow(this->getWindow());
    glfwTerminate();
}

void OpenGLRendererManager::render()
{
    // clear background
    glClearDepth( 1.0 );
    glClearColor(this->clear_color.x * this->clear_color.w, this->clear_color.y * this->clear_color.w, this->clear_color.z * this->clear_color.w, this->clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

GLFWwindow* OpenGLRendererManager::getWindow()
{
    return this->mainWindow->getWindow();
}

GLuint OpenGLRendererManager::getFrame()
{
    return this->textureColorbuffer;
}


void OpenGLRendererManager::drawTriangle()
{
    OpenGLRendererManager::formes->DrawTriangle();
}

void OpenGLRendererManager::drawPlan(float nbrUnits, float scale)
{
    int nbrLinesX = (int)(nbrUnits *2.0f);
    int nbrLinesZ = (int)(nbrUnits *2.0f);
    nbrUnits = (int)(nbrUnits*2.0f * scale);

    glColor4f(1.0, 1.0, 1.0, 0.5); // white transparent
    glPushMatrix();

    // Create all X lines
    for (int xc = 0; xc <= nbrLinesX; xc++)
    {
        glTranslatef(0.0, 0.0, -nbrUnits / 2.0 + xc / (float)(nbrLinesX)*nbrUnits);
        glScalef(nbrUnits, 1.0, 1.0);
        // ligne construite par rapport à son centre
        OpenGLRendererManager::formes->DrawLine();
        glScalef(1.0f / nbrUnits, 1.0, 1.0);
        glTranslatef(0.0, 0.0, -(-nbrUnits / 2.0 + xc / (float)(nbrLinesX)*nbrUnits));
    }
    // Create all Z lines
    glRotatef(90.0f, 0,1,0);
    for (int zc = 0; zc <= nbrLinesZ; zc++)
    {
        glTranslatef(0.0, 0.0, -nbrUnits / 2.0 + zc / (float)(nbrLinesZ)*nbrUnits);
        glScalef(nbrUnits, 1.0, 1.0);
        // ligne construite par rapport à son centre
        OpenGLRendererManager::formes->DrawLine();
        glScalef(1.0f / nbrUnits, 1.0, 1.0);
        glTranslatef(0.0, 0.0, -(-nbrUnits / 2.0 + zc / (float)(nbrLinesZ)*nbrUnits));
    }
    glRotatef(-90.0f, 0, 1, 0);

    glPopMatrix();
}

void OpenGLRendererManager::drawAxis(float echelle)
{
    glPushMatrix();
    glScalef(echelle, echelle, echelle);
    OpenGLRendererManager::formes->DrawAxis();
    glScalef(1.0f / echelle, 1.0f / echelle, 1.0f / echelle);
    glPopMatrix();
}

void OpenGLRendererManager::drawRect2D(const Vector3& dimensions, const Vector3& pos, const Matrix34& transformMatrix)
{
    glPushMatrix();
    glMultMatrixf(transformMatrix.GetMatrix44ForGL().data());
    glScalef(2.f * dimensions.GetX(), 1.0, 2.f * dimensions.GetZ());
    OpenGLRendererManager::formes->DrawCarre();
    glScalef(1.0f / (2.f * dimensions.GetX()), 1.0, 1.0f / (2.f * dimensions.GetZ()));
    glPopMatrix();
}

void OpenGLRendererManager::drawCube(const Vector3& dimensions, const Vector3& pos, const Matrix34& transformMatrix, const Vector3& rot) {

    glPushMatrix();
    //glTranslatef(pos.GetX(), pos.GetY(), pos.GetZ());              // translate to the positon
    //glRotatef(rot.GetX(), 1, 0, 0); // Rotation particle (if necessary)
    //glRotatef(rot.GetY(), 0, 1, 0); // Rotation particle (if necessary)
    //glRotatef(rot.GetZ(), 0, 0, 1); // Rotation particle (if necessary)
    glMultMatrixf(transformMatrix.GetMatrix44ForGL().data());
    //glLoadMatrixf(transformMatrix.Get().data());
    glScalef(2.f * dimensions.GetX(), 2.f * dimensions.GetY(), 2.f * dimensions.GetZ());
    OpenGLRendererManager::formes->DrawCube();
    glScalef(1.0f / (2.f * dimensions.GetX()), 1.0f / (2.f * dimensions.GetY()), 1.0f / (2.f * dimensions.GetZ()));

// debug sphere for rigidbody
    glScalef(2.f * dimensions.GetMaxValue(), 2.f * dimensions.GetMaxValue(), 2.f * dimensions.GetMaxValue());
    OpenGLRendererManager::formes->DrawDebugSphere();
    glScalef(1.0f / (2.f * dimensions.GetMaxValue()), 1.0f / (2.f * dimensions.GetMaxValue()), 1.0f / (2.f * dimensions.GetMaxValue()));

    glPopMatrix();
}

void OpenGLRendererManager::drawSphere(const Vector3& dimensions, const Vector3& pos, const Matrix34& transformMatrix, const Vector3& rot) {

    glPushMatrix();
    //glTranslatef(pos.GetX(), pos.GetY(), pos.GetZ());              // translate to the positon
    //glRotatef(rot.GetX(), 1, 0, 0); // Rotation particle (if necessary)
    //glRotatef(rot.GetY(), 0, 1, 0); // Rotation particle (if necessary)
    //glRotatef(rot.GetZ(), 0, 0, 1); // Rotation particle (if necessary)
    glMultMatrixf(transformMatrix.GetMatrix44ForGL().data());
    //glLoadMatrixf(transformMatrix.Get().data());
    glScalef(2.f * dimensions.GetX(), 2.f * dimensions.GetY(), 2.f * dimensions.GetZ());

    OpenGLRendererManager::formes->DrawSphere();
    glScalef(1.0f / (2.f * dimensions.GetX()), 1.0f / (2.f * dimensions.GetY()), 1.0f / (2.f * dimensions.GetZ()));
    glPopMatrix();
}

bool OpenGLRendererManager::windowShouldClose() {
    return glfwWindowShouldClose(this->mainWindow->getWindow());
}

void OpenGLRendererManager::drawLine(const Vector3 &startPosition, const Vector3 &endPosition) {
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255); // white
    glVertex3f(startPosition.GetX(), startPosition.GetY(), startPosition.GetZ());
    glVertex3f(endPosition.GetX(), endPosition.GetY(), endPosition.GetZ());
    glEnd();
    glEndList();
}
