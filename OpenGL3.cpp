#include "OpenGL3.h"
#include <Windows.h>

OpenGL3::OpenGL3(Simulator* sim)
{
    this->cam = new Camera();
    this->cam->Set(20.0f, -25.0f, 0.0f);
    this->rotationCamDeltaY = 0.0f;

    this->sim = sim;
}

// Clears the current window and draws a triangle.
void OpenGL3::update() {
    ImGuiIO& io = ImGui::GetIO();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); // 3D Projection
    glLoadIdentity();

    // ----- cam ------
    this->rotationCamDeltaY = 0.05f;
    this->cam->AddOrbitalRotationY(this->rotationCamDeltaY);
    LPPOINT pt = new POINT;

    GetCursorPos(pt);
    if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
    {   this->cam->Set(15.0f, pt->y, pt->x);
    
    }
 
    this->cam->Update();


    // -----------
    // draw plan and axis at (0,0,0)
    this->drawPlan(10.0f);
    this->drawAxis(1);

    // -----------
    /*
    // model transform:
    // rotate 45 on Y-axis then move 2 unit up
    glTranslatef(0, 2, 1);              // 2nd transform
    glRotatef(45, 0, 1, 1);               // 1st transform

   
    this->drawCube(3, 2);

    glRotatef(-45*10, 0, 1, 0);               // 1st transform

    glTranslatef(0, 0, 2);              // 2nd transform
    glRotatef(45*5, 1, 1, 1);               // 1st transform

    this->drawCube(3, 2);
    */
    this->DrawAllParticules();
    
    

    // TODO : call functions that create objects
    // ...

    // Flush drawing command buffer to make drawing happen as soon as possible.
    glFlush();


}

void OpenGL3::createTriangle()
{
    // Drawing is done by specifying a sequence of vertices.  The way these
    // vertices are connected (or not connected) depends on the argument to
    // glBegin.  GL_POLYGON constructs a filled polygon.
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.6f, -0.75f, 0.5f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.6f, -0.75f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.75f, 0.0f);
    glEnd();
}

void OpenGL3::drawAxis(float echelle)
{
    glPushMatrix();
    glScalef(echelle, echelle, echelle);
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // rouge
    glColor3ub(0, 255, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // green
    glColor3ub(0, 0, 255); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // bleu
    glEnd();
    glScalef(-echelle, -echelle, -echelle);
    glPopMatrix();
}

void OpenGL3::drawPlan(float nbrUnits)
{
    int nbrLinesX = (int)(nbrUnits *2.0f);
    int nbrLinesZ = (int)(nbrUnits *2.0f);
    nbrUnits = (int)(nbrUnits*2.0f);
    
    glColor3f(1.0, 1.0, 1.0); // white
    glPushMatrix();
    
    glBegin(GL_LINES);
    for (int xc = 0; xc <= nbrLinesX; xc++)
    {
        glVertex3f(-nbrUnits / 2.0 + xc / (float)(nbrLinesX) * nbrUnits,
            0.0,
            nbrUnits / 2.0);
        glVertex3f(-nbrUnits / 2.0 + xc / (float)(nbrLinesX) * nbrUnits,
            0.0,
            nbrUnits / -2.0f);
    }
    for (int zc = 0; zc <= nbrLinesX; zc++)
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

/*
    Dessine un rectangle avec comme point de r�f�rence
    le milieu du c�t� gauche
*/
void OpenGL3::drawRect2D(double largeur, double hauteur)
{
    glBegin(GL_QUADS);
    glVertex2d(0, -hauteur / 2);
    glVertex2d(0, hauteur / 2);
    glVertex2d(largeur, hauteur / 2);
    glVertex2d(largeur, -hauteur / 2);
    glEnd();
}

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

// TODO : Create other functions to create 3D objects with args to change sizes, color and position
// ...

// TODO : Draw plan and 3D axis
// ...

void OpenGL3::DrawAllParticules() {
    for (auto &particule : this->sim->GetParticles())
    {
        glPushMatrix();
        Vector3 pos = particule.GetPosition();
        glTranslatef(pos.GetX(), pos.GetY(), pos.GetZ());              // 2nd transform
        //glRotatef(45, 0, 1, 1);               // 1st transform
        this->drawCube(0.2, 0.2);

        glPopMatrix();
    } 
}