#ifndef Scene_H_
#define Scene_H_
#include "ClassIncludes.h"

#include <vector>
#include "Physics/Particle.h"
#include "3DScene/Camera.h"
#include "3DScene/OpenGLRendererManager.h"
#include "Math/Vector3.h"

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

    // remove all objects
    void reset();

private:
    void drawObjects();
};


#endif // Scene_H_