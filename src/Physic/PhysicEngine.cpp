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

        auto p1 = EngineManager::getInstance().getScene()->GetObject(0);
        auto p2 = EngineManager::getInstance().getScene()->GetObject(1);//ground
        auto p3 = EngineManager::getInstance().getScene()->GetObject(2);//top
        auto p4 = EngineManager::getInstance().getScene()->GetObject(3);//left
        auto p5 = EngineManager::getInstance().getScene()->GetObject(4);//right
//        auto p6 = EngineManager::getInstance().getScene()->GetObject(5);//front
//        auto p7 = EngineManager::getInstance().getScene()->GetObject(6);//back
        EngineManager::getInstance().getScene()->getObjects()->clear();
        EngineManager::getInstance().getScene()->addObject(*p1);
        EngineManager::getInstance().getScene()->addObject(*p2);
        EngineManager::getInstance().getScene()->addObject(*p3);
        EngineManager::getInstance().getScene()->addObject(*p4);
        EngineManager::getInstance().getScene()->addObject(*p5);
//        EngineManager::getInstance().getScene()->addObject(*p6);
//        EngineManager::getInstance().getScene()->addObject(*p7);

        // 1 - Update force (gravity)
        this->forceRegistry->UpdateForce(deltaTime);

        // 2 - Integrate objects
        for (int i = 0; i < this->objects->size(); i++)
        {
            EngineManager::getInstance().console.log("%s %d : %s\n", typeid(*this->objects->at(i)->body).name(), i+1, this->objects->at(i)->body->toString().c_str());
            this->objects->at(i)->body->Integrate(deltaTime);
        }

        // 3 - Add contacts
        //this->contactRegistry->UpdateContacts();
        BVH bvh;
        for (int i = 0; i < this->objects->size(); ++i) {
            Node* node = new Node(this->objects->at(i));
            bvh.insertNode(node);
        }
        bvh.print();
        drawBVH(bvh.root);

        CollisionData* cd = new CollisionData();
        bvh.broadPhaseCheck(cd);
        if(cd->contacts->size()>0){
            for (auto collision : *cd->contacts) {
                auto debug = new Sphere(collision->m_contactPoint, 2);
                debug->setBody(new RigidBody(0.f, collision->m_contactPoint, RigidBody::ShapeType::BoundingSphereDebug, Vector3(2*(sqrtf(2.f)/2.f),2*(sqrtf(2.f)/2.f),2*(sqrtf(2.f)/2.f))));
                debug->body->SetName(u8"PtContact");
                EngineManager::getInstance().getScene()->addObject(*debug);

            }
            this->pause();
            EngineManager::getInstance().console.log("%s\n",cd->toString().c_str());

        }
        //this->contactRegistry->SetContactList(*cd->contacts);

        // 4 - Resolve contacts
        this->contactRegistry->Resolve(deltaTime);
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

void PhysicEngine::drawBVH(Node* node){


    // debug sphere for plan
    auto debug = new Sphere(node->sphere.center, node->sphere.radius);
    debug->setBody(new RigidBody(0.f, node->sphere.center, RigidBody::ShapeType::BoundingSphereDebug, Vector3(node->sphere.radius*(sqrtf(2.f)/2.f),node->sphere.radius*(sqrtf(2.f)/2.f),node->sphere.radius*(sqrtf(2.f)/2.f))));
    debug->body->SetName(u8"Node");
    EngineManager::getInstance().getScene()->addObject(*debug);
    debug = nullptr;

    for (Node* child : node->childNodes)
    {
        drawBVH(child);
    }

}