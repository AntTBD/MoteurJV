#include "OpenGL3.h"
#include <Windows.h>

OpenGL3::OpenGL3(Simulator* sim)
{
    this->cam = new Camera(); // create main camera
    this->cam->Set(400.0f, -0.0f, 0.0f); // set default position
    this->rotationCamDeltaY = 0.0f;

    this->sim = sim;

    this->formes = new Formes();
}

void OpenGL3::InitFormes()
{
    this->formes->Init();
}

/// <summary>
/// Clears the window add camera and draws all objects.
/// </summary>
void OpenGL3::update() {
    ImGuiIO& io = ImGui::GetIO();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set view mode
    glMatrixMode(GL_MODELVIEW); // 3D Projection
    glLoadIdentity();

    // --------------
    // Set camera position and rotation
    //this->rotationCamDeltaY = 0.05f;
    //this->cam->AddOrbitalRotationY(this->rotationCamDeltaY);
    
    // mouse wheel zoom 
    if(io.MouseWheel != 0) this->cam->SetDistance(this->cam->GetDistance() + (float)io.MouseWheel*10.f);
    //move cam on wheel clicked
    if (ImGui::IsMouseDown(2)) {
        this->cam->Add(0, -(float)io.MouseDelta.y, (float)io.MouseDelta.x); // set default position
    }

    // Update Camera
    if (this->cam->getWidth() != io.DisplaySize.x || this->cam->getHeight() != io.DisplaySize.y) {
        this->cam->setSize(io.DisplaySize.x, io.DisplaySize.y);
    }
    this->cam->Update();
    glTranslatef(/*-(float)io.DisplaySize.x / 4.f / 2.f */ 0, -(float)io.DisplaySize.y / 4.f / 2.f, 0);// move cam to be centered has screen
    
    // --------------
    // draw plan and axis at (0,0,0)
    //this->drawPlan(10.0f);

    this->drawPlan(50,10);
    this->drawAxis(10);


    // --------------
    // TODO : call functions that create objects
    this->DrawAllParticules();
    // ...

    // --------------

    // Flush drawing command buffer to make drawing happen as soon as possible.
    glFlush();


}

/// <summary>
/// Create multicolor 2D triangle with glVertex
/// </summary>
void OpenGL3::createTriangle()
{
    this->formes->DrawTriangle();
}

/// <summary>
/// Create axis for 3 dimensions 
/// </summary>
/// <param name="echelle">Length of axis</param>
void OpenGL3::drawAxis(float echelle)
{
    glPushMatrix();
    glScalef(echelle, echelle, echelle);
    this->formes->DrawAxis();
    glScalef(1.0f / echelle, 1.0f / echelle, 1.0f / echelle);
    glPopMatrix();
}

/// <summary>
/// Create plan for nbrUnits positifs
/// </summary>
/// <param name="nbrUnits">Nbr of positive units</param>
void OpenGL3::drawPlan(float nbrUnits, float scale)
{
    int nbrLinesX = (int)(nbrUnits *2.0f);
    int nbrLinesZ = (int)(nbrUnits *2.0f);
    nbrUnits = (int)(nbrUnits*2.0f * scale);
    
    glColor3f(1.0, 1.0, 1.0); // white
    glPushMatrix();
    
    // Create all X lines
    for (int xc = 0; xc <= nbrLinesX; xc++)
    {
        glTranslatef(0.0, 0.0, -nbrUnits / 2.0 + xc / (float)(nbrLinesX)*nbrUnits);
        glScalef(nbrUnits, 1.0, 1.0);
        this->formes->DrawLine();
        glScalef(1.0f / nbrUnits, 1.0, 1.0);
        glTranslatef(0.0, 0.0, -(-nbrUnits / 2.0 + xc / (float)(nbrLinesX)*nbrUnits));
    }
    // Create all Z lines
    glRotatef(90.0f, 0,1,0);
    for (int zc = 0; zc <= nbrLinesZ; zc++)
    {
        glTranslatef(0.0, 0.0, -nbrUnits / 2.0 + zc / (float)(nbrLinesZ)*nbrUnits);
        glScalef(nbrUnits, 1.0, 1.0);
        this->formes->DrawLine();
        glScalef(1.0f / nbrUnits, 1.0, 1.0);
        glTranslatef(0.0, 0.0, -(-nbrUnits / 2.0 + zc / (float)(nbrLinesZ)*nbrUnits));
    }
    glRotatef(-90.0f, 0, 1, 0);

    glPopMatrix();
}

/// <summary>
/// Create 2D rectangle with the middle of the left side as a reference point
/// </summary>
/// <param name="largeur"></param>
/// <param name="hauteur"></param>
void OpenGL3::drawRect2D(double largeur, double hauteur)
{
    glScalef(largeur, hauteur, 1.0);
    this->formes->DrawCarre();
    glScalef(1.0f / largeur, 1.0f / hauteur, 1.0);
}

/// <summary>
/// Create 3D parallelepiped with the center as a reference point
/// </summary>
/// <param name="largeur"></param>
/// <param name="hauteur"></param>
void OpenGL3::drawCube(double largeur, double hauteur) {

    glPushMatrix();
    glScalef(largeur, largeur, largeur);
    this->formes->DrawCube();
    glScalef(1.0f / largeur, 1.0f / largeur, 1.0f / largeur);
    glPopMatrix();
}

/// <summary>
/// Create 3D sphere with the center as a reference point (with specific diametre)
/// </summary>
/// <param name="diametre"></param>
void OpenGL3::DrawSphere(double diametre) {

    glPushMatrix();
    glScalef(diametre, diametre, diametre);
    this->formes->DrawSphere();
    glScalef(1.0f / diametre, 1.0f / diametre, 1.0f / diametre);
    glPopMatrix();
}

/// <summary>
/// Create all particles of the simulator
/// </summary>
void OpenGL3::DrawAllParticules() {
    for (auto &particule : this->sim->GetParticles()) // Browse particles
    {
        glPushMatrix();
        Vector3 pos = particule->GetPosition(); // Get position
        glTranslatef(pos.GetX(), pos.GetY(), pos.GetZ());              // translate to the positon
        //glRotatef(45, 0, 1, 1); // Rotation particle (if necessary)
        //this->drawCube(0.2, 0.2); // create a small cube to simulate particle in 3D
        this->DrawSphere(10); // create a small sphere to simulate particle in 3D

        glPopMatrix();// draw cube and return to center
    } 
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------

// https://badvertex.com/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c.html
GLuint OpenGL3::LoadShader(const char* vertex_path, const char* fragment_path)
{
    /*GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Read shaders

    std::string vertShaderStr = ReadFile::ReadAndReturnContent(vertex_path);
    std::string fragShaderStr = ReadFile::ReadAndReturnContent(fragment_path);
    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;

    // Compile vertex shader

    std::cout << "Compiling vertex shader." << std::endl;
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    // Check vertex shader

    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
    std::cout << &vertShaderError[0] << std::endl;

    // Compile fragment shader

    std::cout << "Compiling fragment shader." << std::endl;
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    // Check fragment shader

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<GLchar> fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
    std::cout << &fragShaderError[0] << std::endl;

    std::cout << "Linking program" << std::endl;
    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError((logLength > 1) ? logLength : 1);
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    std::cout << &programError[0] << std::endl;

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;*/
    return GLuint();
}

