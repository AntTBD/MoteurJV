#include "PhysicEngine.h"

PhysicEngine::PhysicEngine()
{
    this->particleForceRegistry = new ParticleForceRegistry();
    this->particleContactRegistry = new ParticleContactRegistry();
    this->particles = new std::vector<Particle*>();
    this->dT = 0;
    this->isSimulating = false;

}

PhysicEngine::~PhysicEngine()
{
    delete this->particleForceRegistry;
    delete this->particleContactRegistry;
    delete this->particles;
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
    this->particles = EngineManager::getInstance().getScene()->getObjects();

    if (!particles->empty()) {



        // ------ add contacts -------
        // add contacts naive entre particules (=colision entre 2 particules)
        NaiveParticleContactGenerator* naiveParticleContactGenerator = new NaiveParticleContactGenerator(particles, 10);// contacts entre particules de rayon 10
        this->particleContactRegistry->Add(naiveParticleContactGenerator, 2 * this->particles->size());
        // contact avec le sol
        GroundContactGenerator* groundContactGenerator = new GroundContactGenerator(particles, 0.0f);// contact avec le sol à une hauteur de 0
        this->particleContactRegistry->Add(groundContactGenerator, this->particles->size());


        for (int i = 0; i < this->particles->size(); i++)
        {
            // ------ force -------
            // add ressort ancré sur la particule actuelle
            ParticleSpring* particleSpringGenerator = new ParticleSpring(*this->particles->at(i), 5, 50);

            // add tiges or cables between each particles + spring force anchored on actual particle
            for (int k = i + 1; k < this->particles->size(); k++) {
                // ------ contacts -------
                // add contacts cables
                //auto tige = new ParticleRod(this->particles->at(i), this->particles>at(k), 100);// tige de longueur 200
                //this->particleContactRegistry->Add(tige, 1);

                // add contacts tiges
                auto cable = new ParticleCable(this->particles->at(i), this->particles->at(k), 100);// cable de longueur 200
                this->particleContactRegistry->Add(cable, 1);

                // ------ force -------
                // Add spring force
                this->particleForceRegistry->Add(this->particles->at(k), particleSpringGenerator);
            }

            // ------ force -------
            // Add gravity force
            ParticleGravity* particleGravityGenerator = new ParticleGravity();
            this->particleForceRegistry->Add(this->particles->at(i), particleGravityGenerator);
        }


        this->isUpdateFinished = true;

        std::cout << "PhysicEngine ready => init ended " << this->isUpdateFinished << std::endl;
    }
}


void PhysicEngine::update(float deltaTime)
{
    this->dT = deltaTime;
    if (!particles->empty())
    {
        isUpdateFinished = false;

        // 1 - Update force (gravity)
        this->particleForceRegistry->UpdateForce(deltaTime);

        // 2 - Integrate particles
        for (int i = 0; i < this->particles->size(); i++)
        {
            //std::cout << "Particule " << i + 1 << " : " << *this->particles->at(i) << std::endl;
            EngineManager::getInstance().console.log("Particule %d : %s\n", i+1, this->particles->at(i)->toString().c_str());
            this->particles->at(i)->Integrate(deltaTime);
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
    for (auto p : *this->particles)
    {
        delete p;
    }
    this->particles->clear();
    EngineManager::getInstance().getScene()->reset();
    std::cout << "Particles cleared" << std::endl;
}