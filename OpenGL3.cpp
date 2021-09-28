#include "OpenGL3.h"
#include <Windows.h>

OpenGL3::OpenGL3(Simulator* sim)
{
    this->cam = new Camera(); // create main camera
    this->cam->Set(20.0f, -25.0f, 0.0f); // set default position
    this->rotationCamDeltaY = 0.0f;

    this->sim = sim;
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
    this->rotationCamDeltaY = 0.05f;
    this->cam->AddOrbitalRotationY(this->rotationCamDeltaY);
    /* 
    // TODO : perform orbital rotation with mouse
    LPPOINT pt = new POINT;
    GetCursorPos(pt);
    if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
    {
        this->cam->Set(15.0f, pt->y, pt->x);

    }*/
    // Update Camera
    this->cam->Update();
    
    // --------------
    // draw plan and axis at (0,0,0)
    this->drawPlan(10.0f);
    this->drawAxis(1);
    
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
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.6f, -0.75f, 0.5f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.6f, -0.75f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.75f, 0.0f);
    glEnd();
}

/// <summary>
/// Create axis for 3 dimensions 
/// </summary>
/// <param name="echelle">Length of axis</param>
void OpenGL3::drawAxis(float echelle)
{
    glPushMatrix();
    glScalef(echelle, echelle, echelle);
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // x => rouge
    glColor3ub(0, 255, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // y => green
    glColor3ub(0, 0, 255); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // z => bleu
    glEnd();
    glScalef(-echelle, -echelle, -echelle);
    glPopMatrix();
}

/// <summary>
/// Create plan for nbrUnits positifs
/// </summary>
/// <param name="nbrUnits">Nbr of positive units</param>
void OpenGL3::drawPlan(float nbrUnits)
{
    int nbrLinesX = (int)(nbrUnits *2.0f);
    int nbrLinesZ = (int)(nbrUnits *2.0f);
    nbrUnits = (int)(nbrUnits*2.0f);
    
    glColor3f(1.0, 1.0, 1.0); // white
    glPushMatrix();
    
    glBegin(GL_LINES);
    // Create all X lines
    for (int xc = 0; xc <= nbrLinesX; xc++)
    {
        glVertex3f(-nbrUnits / 2.0 + xc / (float)(nbrLinesX) * nbrUnits,
            0.0,
            nbrUnits / 2.0);
        glVertex3f(-nbrUnits / 2.0 + xc / (float)(nbrLinesX) * nbrUnits,
            0.0,
            nbrUnits / -2.0f);
    }
    // Create all Z lines
    for (int zc = 0; zc <= nbrLinesZ; zc++)
    {
        glVertex3f(nbrUnits / 2.0,
            0.0,
            -nbrUnits / 2.0 + zc / (float)(nbrLinesZ) * nbrUnits);
        glVertex3f(nbrUnits / -2.0,
            0.0,
            -nbrUnits / 2.0 + zc / (float)(nbrLinesZ) * nbrUnits);
    }
    glEnd();

    glPopMatrix();
}

/// <summary>
/// Create 2D rectangle with the middle of the left side as a reference point
/// </summary>
/// <param name="largeur"></param>
/// <param name="hauteur"></param>
void OpenGL3::drawRect2D(double largeur, double hauteur)
{
    glBegin(GL_QUADS);
    glVertex2d(0, -hauteur / 2);
    glVertex2d(0, hauteur / 2);
    glVertex2d(largeur, hauteur / 2);
    glVertex2d(largeur, -hauteur / 2);
    glEnd();
}

/// <summary>
/// Create 3D parallelepiped with the center as a reference point
/// </summary>
/// <param name="largeur"></param>
/// <param name="hauteur"></param>
void OpenGL3::drawCube(double largeur, double hauteur) {

    glPushMatrix();
    glScalef(largeur, largeur, largeur);
    glScalef(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);

    glColor3ub(255, 0, 0); //face rouge
    glVertex3d(1, 1, 1);
    glVertex3d(1, 1, -1);
    glVertex3d(-1, 1, -1);
    glVertex3d(-1, 1, 1);

    glColor3ub(0, 255, 0); //face verte
    glVertex3d(1, -1, 1);
    glVertex3d(1, -1, -1);
    glVertex3d(1, 1, -1);
    glVertex3d(1, 1, 1);

    glColor3ub(0, 0, 255); //face bleue
    glVertex3d(-1, -1, 1);
    glVertex3d(-1, -1, -1);
    glVertex3d(1, -1, -1);
    glVertex3d(1, -1, 1);

    glColor3ub(255, 255, 0); //face jaune
    glVertex3d(-1, 1, 1);
    glVertex3d(-1, 1, -1);
    glVertex3d(-1, -1, -1);
    glVertex3d(-1, -1, 1);

    glColor3ub(0, 255, 255); //face cyan
    glVertex3d(1, 1, -1);
    glVertex3d(1, -1, -1);
    glVertex3d(-1, -1, -1);
    glVertex3d(-1, 1, -1);

    glColor3ub(255, 0, 255); //face magenta
    glVertex3d(1, -1, 1);
    glVertex3d(1, 1, 1);
    glVertex3d(-1, 1, 1);
    glVertex3d(-1, -1, 1);

    glEnd();
    glPopMatrix();
}

/// <summary>
/// Create all particles of the simulator
/// </summary>
void OpenGL3::DrawAllParticules() {
    for (auto &particule : this->sim->GetParticles()) // Browse particles
    {
        glPushMatrix();
        Vector3 pos = particule.GetPosition(); // Get position
        glTranslatef(pos.GetX(), pos.GetY(), pos.GetZ());              // translate to the positon
        //glRotatef(45, 0, 1, 1); // Rotation particle (if necessary)
        this->drawCube(0.2, 0.2); // create a small cube to simulate particle in 3D

        glPopMatrix();// draw cube and return to center
    } 
}

// TODO : Create other functions to create 3D objects with args to change sizes, color and position
// ...

