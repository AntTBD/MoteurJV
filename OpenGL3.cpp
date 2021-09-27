#include "OpenGL3.h"

OpenGL3::OpenGL3()
{
    this->textureSceneRendered = NULL;
}
void DrawNet(GLfloat size, GLint LinesX, GLint LinesZ)
{
    glBegin(GL_LINES);
    for (int xc = 0; xc < LinesX; xc++)
    {
        glVertex3f(-size / 2.0 + xc / (GLfloat)(LinesX - 1) * size,
            0.0,
            size / 2.0);
        glVertex3f(-size / 2.0 + xc / (GLfloat)(LinesX - 1) * size,
            0.0,
            size / -2.0);
    }
    for (int zc = 0; zc < LinesX; zc++)
    {
        glVertex3f(size / 2.0,
            0.0,
            -size / 2.0 + zc / (GLfloat)(LinesZ - 1) * size);
        glVertex3f(size / -2.0,
            0.0,
            -size / 2.0 + zc / (GLfloat)(LinesZ - 1) * size);
    }
    glEnd();
}
// Clears the current window and draws a triangle.
void OpenGL3::create3dModels() {
    ImGuiIO& io = ImGui::GetIO();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glMatrixMode(GL_PROJECTION);// 2D Projection
    glMatrixMode(GL_MODELVIEW); // 3D Projection
    glLoadIdentity();

    fov = 90.0f;
    nearF = 0.2f;
    far = 100.0f;
    xX = 5.0f;
    yY = 2.5f;
    zZ = 5.0f;
/*
    // https://opengl.developpez.com/tutoriels/opengl-tutorial/6-clavier-et-souris/
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rotationDegrees), glm::vec3(1.0f, 1.0f, 0.0f));
    glm::mat4 modelTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f));
    // Matrice de vue
    glm::mat4 view = glm::lookAt(
        glm::vec3(yY, xX, zZ), // La caméra est là
        glm::vec3(0.0f, 0.0f, 0.0f), // et regarde ici : à la même position, plus la « direction »
        glm::vec3(0.0f, 1.0f, 0.0f) // la tête est vers le haut (définir à 0,-1,0 pour voir à l'envers) 
    );
    glm::mat4 modelview = view * modelTransform * rotation;
    // Matrice de projection : champ de vision 45°, ration 4:3, distance d'affiche : 0.1 unit <-> 100 units 
    //glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), (float)800 / (float)600, nearF, far);
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), (float)io.DisplaySize.x / (float)io.DisplaySize.y, nearF, far);

    rotationDegrees += 0.5f;

    // https://github.com/ocornut/imgui/issues/2760#issuecomment-526557526
    glLoadMatrixf(glm::value_ptr(projectionMatrix));//3D projection
    //glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, nearF, far);// GL_PROJECTION 2D 
    //glOrtho(-1.0, 1.0, -1.0, 1.0, nearF, far);// Orthographic Projection
 //   glTranslatef(-xX, -yY, -zZ);
    //glRotatef(-25, 1, 0, 0);
 //   glRotatef(-rotationDegrees, 0, 1, 0);
    //glRotatef(-25, 0, 0, 1);

    // http://www.songho.ca/opengl/gl_matrix.html#example1
    glTranslatef(0, 0, -camDist);       // 3rd: translate along z
    glRotatef(45, 1, 0, 0);       // 2nd: rotate on x-axis
    glRotatef(-rotationDegrees, 0, 1, 0);       // 1st: rotate on y-axis
    // TODO : http://www.songho.ca/opengl/gl_camera.html#lookat

    //glMatrixMode(GL_MODELVIEW); // 3D Projection
    //glLoadIdentity();
*/
    // --------
    rotationDegrees += 0.25f;
    //camDist += 0.1f;

    glLoadMatrixf(glm::value_ptr(camera(camDist,glm::vec2(glm::radians(rotationDegrees), glm::radians(-25.0f)))));
    // --------

    this->drawPlan(10.0f);
    this->drawAxis(1);

// model transform:
// rotate 45 on Y-axis then move 2 unit up
    glTranslatef(0, 2, 1);              // 2nd transform
    glRotatef(rotationDegrees, 0, 1, 1);               // 1st transform

    // 
    // Sélectionne les triangles dont les normales ne sont pas vers la caméra
    //glEnable(GL_CULL_FACE);

    //glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(modelview)); 
   // glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));



    //glRotated(45, 0, 1, 0);

    
  //  glTranslatef(0.0, 0.8, 0.0);
    //this->createTriangle();
    //this->drawRect2D(3,2);
    this->drawCube(3, 2);

    glRotatef(-rotationDegrees*10, 0, 1, 0);               // 1st transform

    glTranslatef(0, 0, 2);              // 2nd transform
    glRotatef(rotationDegrees*5, 1, 1, 1);               // 1st transform

    this->drawCube(3, 2);


   // glScalef(3.0, 1.0, 3.0);

    
    

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
    glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
    glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
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
    Dessine un rectangle avec comme point de référence
    le milieu du côté gauche
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

