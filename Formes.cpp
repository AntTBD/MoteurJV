#include "Formes.h"

Formes::Formes()
{
    cube = 0;
    sphere = 0;
    axes = 0;
    line = 0;
    triangle = 0;
    carre = 0;
}

void Formes::Init()
{
    CreateCube();
    CreateSphere();
    CreateAxis();
    CreateLine();
    CreateTriangle();
    CreateCarre();
}

void Formes::DrawCube()
{
    glCallList(cube);
}

void Formes::DrawSphere()
{
    glCallList(sphere);
}

void Formes::DrawAxis()
{
    glCallList(axes);
}

void Formes::DrawLine()
{
    glCallList(line);
}

void Formes::DrawTriangle()
{
    glCallList(triangle);
}

void Formes::DrawCarre()
{
    glCallList(carre);
}

void Formes::CreateCube()
{
    //cube = index;
    cube = glGenLists(1);
    glNewList(cube, GL_COMPILE);
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
    glScalef(2.0, 2.0, 2.0);
    glEndList();
}

void Formes::CreateSphere()
{
    sphere = glGenLists(1);
    glNewList(sphere, GL_COMPILE);
    ///////////////////////////////////////////////////
    // from https://stackoverflow.com/questions/7687148/drawing-sphere-in-opengl-without-using-glusphere#answer-7687413
    double r = 0.5f;// rayon
    int lats = 20;// nbr de lignes horizontales
    int longs = 20;// nbr de lignes verticales
    int i, j;
    for (i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
        double z0 = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double)i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double)(j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            glColor3ub(255.0f / longs * x, 255.0f / longs * y, 255.0f / lats * i); // change color
            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(r * x * zr0, r * y * zr0, r * z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(r * x * zr1, r * y * zr1, r * z1);
        }
        glEnd();
    }
    ///////////////////////////////////////////////////
    glEndList();
}

void Formes::CreateAxis()
{
    axes = glGenLists(1);
    glNewList(axes, GL_COMPILE);
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // x => rouge
    glColor3ub(0, 255, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // y => green
    glColor3ub(0, 0, 255); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // z => bleu
    glEnd();
    glEndList();
}

void Formes::CreateLine()
{
    line = glGenLists(1);
    glNewList(line, GL_COMPILE);
    // ligne construite par rapport à son centre
    glBegin(GL_LINES);
    glVertex3f(-0.5f, 0, 0);
    glVertex3f(0.5f, 0, 0);
    glEnd();
    glEndList();
}

void Formes::CreateTriangle()
{
    triangle = glGenLists(1);
    glNewList(triangle, GL_COMPILE);
    // triangle construit par rapport à son centre
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.6f, -0.75f, 0.5f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.6f, -0.75f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.75f, 0.0f);
    glEnd();
    glEndList();
}

void Formes::CreateCarre()
{
    carre = glGenLists(1);
    glNewList(carre, GL_COMPILE);
    // carre construit par rapport à son centre
    glBegin(GL_QUADS);
    glVertex2d(0, -1.0f / 2.0f);
    glVertex2d(0, 1.0f / 2.0f);
    glVertex2d(1.0f / 2.0f, 1.0f / 2.0f);
    glVertex2d(1.0f / 2.0f, -1.0f / 2.0f);
    glEnd();
    glEndList();
}
