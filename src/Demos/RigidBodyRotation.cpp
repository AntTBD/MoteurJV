#include "RigidBodyRotation.h"

void RigidBodyRotation::GenerateScene()
{
    // clear all objects added in the scene
    EngineManager::getInstance().getScene()->reset();

    std::vector<RigidBody*>* cars = new std::vector<RigidBody*>();

    float mass = 10.f;
    Vector3 dimension(10, 5, 5);

    // ================ cars =================
    // object
    Vector3 position(-65, 15, 10);
    Vector3 velocity(15.f, 150.f, 0);
    Vector3 angularVelocity(0.5f, 0.2f, 0.3f);
    auto obj = new RigidBody(mass, position,velocity, Quaternion(), angularVelocity, RigidBody::ShapeType::Cube, dimension);
    obj->SetName("RigidBody");
    EngineManager::getInstance().getScene()->addObject(*obj);
    // ================ =======================


    // =============== gravity================
    Gravity* gravityGenerator = new Gravity();
    EngineManager::getInstance().getPhysicEngine()->getForceRegistry()->Add(obj, gravityGenerator);

    // ==================== contacts ====================
    // contact avec le ground
    GroundContactGenerator* groundContactGenerator = new GroundContactGenerator(EngineManager::getInstance().getScene()->getObjects(), 0, false, Vector3(0,1,0));// contact avec le sol à une hauteur de -100
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(groundContactGenerator, EngineManager::getInstance().getScene()->getObjects()->size());


    EngineManager::getInstance().console.logSuccess("Rigidbody initial velocity demo has been generated\n");
}
