#include "CarCollision.h"

void CarCollision::GenerateScene()
{
    std::vector<RigidBody*>* cars = new std::vector<RigidBody*>();

    float mass = 10.f;
    Vector3 carDimension(30, 10, 20);

    // ================ cars =================
    // car1
    Vector3 positionCar1(-65, carDimension.GetY(), 10);
    Vector3 eulerRotationCar1(0, 20, 0);
    Vector3 angularRotationCar1(0.5f, 0.2f, 0.3f);
    cars->push_back(new RigidBody(mass, positionCar1,Vector3(), Quaternion::EulerInDegreesToQuaternion(eulerRotationCar1),angularRotationCar1, RigidBody::ShapeType::Cube, carDimension));
    EngineManager::getInstance().getScene()->addObject(*cars->at(0));

    // car2
    Vector3 positionCar2(65, carDimension.GetY(), 0);
    cars->push_back(new RigidBody(mass, positionCar2, RigidBody::ShapeType::Cube, carDimension));
    EngineManager::getInstance().getScene()->addObject(*cars->at(1));
    // ================ =======================

    // ================ walls =================
    // ground
    Vector3 groundDimension(100, 0, 100);
    Vector3 groundPosition(0, -100, 0);
    Vector3 groundEulerRotation(0, 0, 0);
    auto ground = new RigidBody(mass, groundPosition, Quaternion::EulerInDegreesToQuaternion(groundEulerRotation), RigidBody::ShapeType::Plan, groundDimension);
    EngineManager::getInstance().getScene()->addObject(*ground);
    // top
    Vector3 topDimension = groundDimension;
    Vector3 topPosition(0, 100, 0);
    Vector3 topEulerRotation(180, 0, 0);
    auto top = new RigidBody(mass, topPosition, Quaternion::EulerInDegreesToQuaternion(topEulerRotation), RigidBody::ShapeType::Plan, topDimension);
    EngineManager::getInstance().getScene()->addObject(*top);
    // left
    Vector3 leftDimension = groundDimension;
    Vector3 leftPosition(-100, 0, 0);
    Vector3 leftEulerRotation(90, 0, 90);
    auto left = new RigidBody(mass, leftPosition, Quaternion::EulerInDegreesToQuaternion(leftEulerRotation), RigidBody::ShapeType::Plan, leftDimension);
    EngineManager::getInstance().getScene()->addObject(*left);
    // right
    Vector3 rightDimension = groundDimension;
    Vector3 rightPosition(100, 0, 0);
    Vector3 rightEulerRotation(90, 0, -90);
    auto right = new RigidBody(mass, rightPosition, Quaternion::EulerInDegreesToQuaternion(rightEulerRotation), RigidBody::ShapeType::Plan, rightDimension);
    EngineManager::getInstance().getScene()->addObject(*right);
    // front
    Vector3 frontDimension = groundDimension;
    Vector3 frontPosition(0, 0, -100);
    Vector3 frontEulerRotation(-90, 0, 0);
    auto front = new RigidBody(mass, frontPosition, Quaternion::EulerInDegreesToQuaternion(frontEulerRotation), RigidBody::ShapeType::Plan, frontDimension);
    EngineManager::getInstance().getScene()->addObject(*front);
    // back (without draw)
    Vector3 backDimension = groundDimension;
    Vector3 backPosition(0, 0, 100);
    Vector3 backEulerRotation(90, 0, 0);
    auto back = new RigidBody(mass, backPosition, Quaternion::EulerInDegreesToQuaternion(backEulerRotation), RigidBody::ShapeType::Plan, backDimension);
    EngineManager::getInstance().getScene()->addObject(*back);
    // ===========================================

    std::vector<RigidBody*>* allObjectsWithoutWalls = new std::vector<RigidBody*>();
    // ------ force -------
    ParticleGravity* particleGravityGenerator = new ParticleGravity();
    // Add gravity force on each objects of the scene
    for (int i = 0; i<EngineManager::getInstance().getScene()->getObjects()->size(); i++) {
        auto obj = EngineManager::getInstance().getScene()->GetObject(i);
        if(obj->GetShapeType() != RigidBody::ShapeType::Plan) {
            // =============== gravity================
            EngineManager::getInstance().getPhysicEngine()->getForceRegistry()->Add(obj, particleGravityGenerator);
            allObjectsWithoutWalls->push_back(obj);
        }
    }

    // ==================== contacts ====================
    // ------ add contacts -------
    // add contacts naive entre chaque objets (=colision entre 2 particules)
    NaiveParticleContactGenerator *naiveParticleContactGenerator = new NaiveParticleContactGenerator(allObjectsWithoutWalls);// contacts entre particules de rayon 10
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(naiveParticleContactGenerator, 2 * allObjectsWithoutWalls->size());

    // contact avec le ground
    GroundContactGenerator* groundContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, groundPosition.GetY(),false, Vector3(0,1,0));// contact avec le sol à une hauteur de -100
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(groundContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le top
    GroundContactGenerator* topContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, topPosition.GetY(), true, Vector3(0,1,0));// contact avec le top à une hauteur de 100
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(topContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le left
    GroundContactGenerator* leftContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, leftPosition.GetX(), false, Vector3(1,0,0));// contact avec le top à une hauteur de 100
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(leftContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le right
    GroundContactGenerator* rightContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, rightPosition.GetX(),true, Vector3(1,0,0));// contact avec le top à une hauteur de 100
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(rightContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le front
    GroundContactGenerator* frontContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, frontPosition.GetZ(),false, Vector3(0,0,1));// contact avec le top à une hauteur de 100
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(frontContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le back
    GroundContactGenerator* backContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, backPosition.GetZ(),true, Vector3(0,0,1));// contact avec le top à une hauteur de 100
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(backContactGenerator, allObjectsWithoutWalls->size());

}
