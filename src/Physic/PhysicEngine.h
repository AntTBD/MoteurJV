#ifndef PhysicEngine_H_
#define PhysicEngine_H_
#include "../ClassIncludes.h"

#include "Particle.h"
// forces
#include "Forces/ForceRegistry.h"
#include "Forces/Gravity.h"
#include "Forces/Spring.h"
// contacts
#include "Contacts/ContactRegistry.h"
#include "Contacts/NaiveContactGenerator.h"
#include "Contacts/GroundContactGenerator.h"
#include "Contacts/Cable.h"
#include "Contacts/Rod.h"
// include threads
#include <thread>

// engine to get scene and objects
#include "../EngineManager.h"


//////////////////////////////////////////
//          change type of objects (Particle - RigidBody)
#define Object RigidBody
//////////////////////////////////////////

class PhysicEngine {
private:
    std::vector<Object*>* objects; // copy of objects in the scene for simulation

    ForceRegistry* forceRegistry;
    ContactRegistry* contactRegistry;

    bool isPaused = false;
    bool isUpdateFinished = false;

    // Simulation
    // to know if thread is running
    bool isSimulating;
    std::thread physicEngineThread;
public:
    float dT; // init at the beginning of .cpp

    PhysicEngine();
    ~PhysicEngine();

    // start thread
    void startSimulation();
    void pause();
    void togglePause();
    void resume();
    void stop();

    bool isRunning();

    ForceRegistry* getForceRegistry();
    ContactRegistry* getContactRegistry();

private:

    void init();

    void update(float deltaTime);// Update acceleration, speed and position of all objects in the simulator

    // Thread : Update all objects of the simulator every 16.6ms
    void simulate();
    // Clear the object vector
    void clearObjectsAndRegisters();

    bool isUpdated() const;

};

#endif // PhysicEngine_H_