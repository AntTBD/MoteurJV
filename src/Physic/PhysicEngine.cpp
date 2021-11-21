#include "PhysicEngine.h"

PhysicEngine::PhysicEngine()
{
    this->particleForceRegistry = new ParticleForceRegistry();
    this->particleContactRegistry = new ParticleContactRegistry();
    this->objects = new std::vector<Object*>();
    this->dT = 0;
    this->isSimulating = false;

}

PhysicEngine::~PhysicEngine()
{
    delete this->particleForceRegistry;
    delete this->particleContactRegistry;
    delete this->objects;
}

void PhysicEngine::startSimulation()
{
    // Make new thread running the Simulate() function
    this->physicEngineThread = std::thread{ &PhysicEngine::simulate, this };
}

void PhysicEngine::simulate()
{
    std::cout << "Start" << std::endl;
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
        this->particleForceRegistry->UpdateForce(deltaTime);

        // 2 - Integrate particles
        for (int i = 0; i < this->objects->size(); i++)
        {
            //std::cout << "Particule " << i + 1 << " : " << *this->particles->at(i) << std::endl;
            EngineManager::getInstance().console.log("%s %d : %s\n", typeid(*this->objects->at(i)).name(), i+1, this->objects->at(i)->toString().c_str());
            this->objects->at(i)->Integrate(deltaTime);
        }

        // 3 - Add contacts
        this->particleContactRegistry->UpdateContacts();

        // 4 - Resolve contacts
        this->particleContactRegistry->Resolve(deltaTime);

        isUpdateFinished = true;

    }
}

void PhysicEngine::pause()
{
    std::cout << "Pause" << std::endl;
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
    std::cout << "Resume" << std::endl;
    this->isPaused = false;
}

void PhysicEngine::stop()
{
    std::cout << "Stop" << std::endl;
    this->dT = 0;
    this->isSimulating = false;

    if (this->physicEngineThread.joinable()) {
        this->physicEngineThread.join();
    }
    this->clearParticlesAndRegisters();
    this->resume(); // Set simulation back to unpaused if we cleared while it was paused


}

bool PhysicEngine::isUpdated() const
{
    return this->isUpdateFinished;
}

void PhysicEngine::clearParticlesAndRegisters()
{
    // clear registries
    this->particleForceRegistry->Clear();
    this->particleContactRegistry->Clear();

    // delete particles
    for (auto p : *this->objects)
    {
        delete p;
    }
    this->objects->clear();
    EngineManager::getInstance().getScene()->reset();
    std::cout << "Particles cleared" << std::endl;
}

bool PhysicEngine::isRunning() {
    return this->isSimulating;
}

ParticleForceRegistry *PhysicEngine::getForceRegistry() {
    return this->particleForceRegistry;
}

ParticleContactRegistry *PhysicEngine::getContactRegistry() {
    return this->particleContactRegistry;
}
