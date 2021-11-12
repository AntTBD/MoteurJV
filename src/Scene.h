#pragma once

#include <vector>
#include "../Particle.h"
#include "../Camera.h"
#include "3DScene/OpenGLRendererManager.h"
#include "../Vector3.h"

//////////////////////////////////////////
//          change type of objects (Particle - RigidBody)
#define Object Particle
//////////////////////////////////////////

class Scene {
private:
    // Orbital camera
    Camera* cam;
    std::vector<Object*>* objects;
public:
    Scene();
    ~Scene();

    std::vector<Object*>* getObjects();
    std::vector<Object*> getObjectsByCopy() const;
    Camera* getCamera();

    void addObject(Object& object);
    Object* GetObject(int id);

    void draw();

private:
    void drawObjects();
};
