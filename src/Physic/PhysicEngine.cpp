#include "PhysicEngine.h"

PhysicEngine::PhysicEngine()
{
    this->forceRegistry = new ForceRegistry();
    this->contactRegistry = new ContactRegistry();
    this->objects = new std::vector<Object*>();
    this->dT = 0;
    this->isSimulating = false;

}

PhysicEngine::~PhysicEngine()
{
    delete this->forceRegistry;
    delete this->contactRegistry;
    delete this->objects;
}

void PhysicEngine::startSimulation()
{
    // Make new thread running the Simulate() function
    this->physicEngineThread = std::thread{ &PhysicEngine::simulate, this };
}

void PhysicEngine::simulate()
{
    EngineManager::getInstance().console.logSuccess("Start\n");
    // init engine
    this->init();

    float deltaTimeTarget = 16.6f;
    float deltaTime = 0.0f;
    this->isSimulating = true;

    auto time = std::chrono::high_resolution_clock::now();

    while (this->isSimulating)
    {
        auto now = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> deltaTimeDuration = now - time;
        deltaTime += deltaTimeDuration.count();
        time = now;

        if (deltaTime >= deltaTimeTarget)
        {
            if (!this->isPaused && this->isUpdated()) // No update if simulator is paused
            {
                this->update(deltaTime / 1000.0f);
            }
            deltaTime = 0.0f;
        }
    }
}

void PhysicEngine::init()
{
    // copy objects
    this->objects = EngineManager::getInstance().getScene()->getObjects();




    this->isUpdateFinished = true;

    std::cout << "PhysicEngine ready => init ended " << this->isUpdateFinished << std::endl;

}


void PhysicEngine::update(float deltaTime)
{
    this->dT = deltaTime;
    if (!objects->empty())
    {
        isUpdateFinished = false;

        // 1 - Update force (gravity)
        this->forceRegistry->UpdateForce(deltaTime);


        // 3 - Add contacts
        this->contactRegistry->UpdateContacts();

        // 4 - Resolve contacts
        this->contactRegistry->Resolve(deltaTime);

        // 2 - Integrate objects
        for (int i = 0; i < this->objects->size(); i++)
        {
            EngineManager::getInstance().console.log("%s %d : %s\n", typeid(*this->objects->at(i)).name(), i+1, this->objects->at(i)->toString().c_str());
            this->objects->at(i)->Integrate(deltaTime);
        }
        isUpdateFinished = true;

    }
}

void PhysicEngine::pause()
{
    EngineManager::getInstance().console.logWarning("Pause\n");
    this->isPaused = true;
}

void PhysicEngine::togglePause()
{
    std::cout << "Toggle Pause" << std::endl;
    if(this->isPaused){
        this->resume();
    }else{
        this->pause();
    }
}

void PhysicEngine::resume()
{
    EngineManager::getInstance().console.logWarning("Resume\n");

    this->isPaused = false;
}

void PhysicEngine::stop()
{
    EngineManager::getInstance().console.logWarning("Stop\n");
    this->dT = 0;
    this->isSimulating = false;

    if (this->physicEngineThread.joinable()) {
        this->physicEngineThread.join();
    }
    this->clearObjectsAndRegisters();

    this->isPaused = false; // Set simulation back to unpaused if we cleared while it was paused


}

bool PhysicEngine::isUpdated() const
{
    return this->isUpdateFinished;
}

void PhysicEngine::clearObjectsAndRegisters()
{
    // clear registries
    this->forceRegistry->Clear();
    this->contactRegistry->Clear();

    // delete objects
    for (auto p : *this->objects)
    {
        delete p;
    }
    this->objects->clear();
    EngineManager::getInstance().getScene()->reset();
    EngineManager::getInstance().console.logSuccess("Objects & Registers cleared\n");

}

bool PhysicEngine::isRunning() {
    return this->isSimulating;
}

ForceRegistry *PhysicEngine::getForceRegistry() {
    return this->forceRegistry;
}

ContactRegistry *PhysicEngine::getContactRegistry() {
    return this->contactRegistry;
}
