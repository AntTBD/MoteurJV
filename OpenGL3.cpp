#include "OpenGL3.h"

OpenGL3::OpenGL3()
{
    this->textureSceneRendered = NULL;
}

// Clears the current window and draws a triangle.
void OpenGL3::create3dModels() {

    
    this->createTriangle();

    // TODO : call functions that create objects
    // ...

    // Flush drawing command buffer to make drawing happen as soon as possible.
    //glFlush();


}

void OpenGL3::createTriangle()
{
    // Drawing is done by specifying a sequence of vertices.  The way these
    // vertices are connected (or not connected) depends on the argument to
    // glBegin.  GL_POLYGON constructs a filled polygon.
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
    glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
    glEnd();
}

// TODO : Create other functions to create 3D objects with args to change sizes, color and position
// ...

// TODO : Draw plan and 3D axis
// ...