#include "OpenGLRendererManager.h"

// GLFW Callback error print messages as std error
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

OpenGLRendererManager::OpenGLRendererManager(MainWindow* mainWindow) :
    mainWindow(mainWindow)
{
    // set clear color
    this->clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // add input manager /// TODO not shure if in good place
    this->inputManager = new InputManager();

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

    // glfw window creation
    // --------------------
    this->mainWindow->setWindow(glfwCreateWindow(this->mainWindow->getWidth(), this->mainWindow->getHeight(),  this->mainWindow->getTitle(), NULL, NULL));
    if (!this->getWindow()) {
        fprintf(stderr, "Failed to create window with graphics context\n");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(this->getWindow());
    glfwSwapInterval(1); // Enable vsync

    /// TODO add shaders setup



    // configure global opengl state to be used with 3D view mode
    glEnable(GL_DEPTH_TEST);
}

OpenGLRendererManager::~OpenGLRendererManager()
{
    /// TODO: delete buffers


    glfwDestroyWindow(this->getWindow());
    glfwTerminate();
}

void OpenGLRendererManager::render()
{
    if(!glfwWindowShouldClose(this->getWindow())){
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        // check inputs /// TODO not shure if it is in good place
        this->inputManager->update(this->mainWindow);

        // clear background
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /// TODO to be changed
        {
            // Set view mode
            glMatrixMode(GL_MODELVIEW); // 3D Projection
            glLoadIdentity();

            // Update Camera
//////////////////////////////////////////////
            // from https://github.com/g-truc/glm (perspective var changed to use ours)
            float translate = 10.0f; // camDist
            float rotationOnY = -45.0f; // rotation angle autour du centre
            float rotationOnX = 45.0f; // angle en hauteur
            glm::vec2 const& rotate = glm::vec2(glm::radians(rotationOnY), glm::radians(rotationOnX));
            float nearF = 0.2f;
            float far = 10000.0f;
            ImGuiIO& io = ImGui::GetIO();
            glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)io.DisplaySize.x / (float)io.DisplaySize.y, nearF, far);
            glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -translate));
            View = glm::rotate(View, rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
            View = glm::rotate(View, rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

            glLoadMatrixf(glm::value_ptr(Projection * View * Model));

            // draw axis
            glPushMatrix();
            glBegin(GL_LINES);
            glColor3ub(255, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // x => rouge
            glColor3ub(0, 255, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // y => green
            glColor3ub(0, 0, 255); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // z => bleu
            glEnd();
            glPopMatrix();


            // Flush drawing command buffer to make drawing happen as soon as possible.
            //glFlush();
/////////////////////////////////////////////

        }
    }
}

GLFWwindow* OpenGLRendererManager::getWindow()
{
    return this->mainWindow->getWindow();
}

unsigned int OpenGLRendererManager::getFrame()
{
    return this->textureColorbuffer;
}