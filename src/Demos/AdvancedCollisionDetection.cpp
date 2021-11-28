#include "AdvancedCollisionDetection.h"


void AdvancedCollisionDetection::GenerateScene()
{
    // clear all objects added in the scene
    EngineManager::getInstance().getScene()->reset();


    float mass = 50.f;
    Vector3 boiteDimension(15, 5, 10);
    // boite
    Vector3 boitePosition(-165, boiteDimension.GetMaxValue()+5, 0);
    Vector3 boiteEulerRotation(0, 0, 0);
    Vector3 boiteVelocity(500.f, 0.f, 0.f);
    Vector3 boiteAngularVelocity(0.f, 0.f, 0.0f);
    auto boite = new RigidBody(mass, boitePosition,boiteVelocity, Quaternion::EulerInDegreesToQuaternion(boiteEulerRotation), boiteAngularVelocity, RigidBody::ShapeType::Cube, boiteDimension);
    boite->SetName(u8"Boîte");
    EngineManager::getInstance().getScene()->addObject(*boite);


    // ================ walls =================
    // Ground
    Vector3 groundDimension(200, 0, 200);
    Vector3 groundPosition(0, -0, 0);
    Vector3 groundEulerRotation(0, 0, 0);
    auto ground = new RigidBody(0, groundPosition, Quaternion::EulerInDegreesToQuaternion(groundEulerRotation), RigidBody::ShapeType::Plan, groundDimension);
    ground->SetName("Ground");
    EngineManager::getInstance().getScene()->addObject(*ground);
    // Top
    Vector3 topDimension = groundDimension;
    Vector3 topPosition(0, 400, 0);
    Vector3 topEulerRotation(180, 0, 0);
    auto top = new RigidBody(0, topPosition, Quaternion::EulerInDegreesToQuaternion(topEulerRotation), RigidBody::ShapeType::Plan, topDimension);
    top->SetName("Top");
    EngineManager::getInstance().getScene()->addObject(*top);
    // Left
    Vector3 leftDimension = groundDimension;
    Vector3 leftPosition(-200, 200, 0);
    Vector3 leftEulerRotation(90, 0, 90);
    auto left = new RigidBody(0, leftPosition, Quaternion::EulerInDegreesToQuaternion(leftEulerRotation), RigidBody::ShapeType::Plan, leftDimension);
    left->SetName("Left");
    EngineManager::getInstance().getScene()->addObject(*left);
    // Right
    Vector3 rightDimension = groundDimension;
    Vector3 rightPosition(200, 200, 0);
    Vector3 rightEulerRotation(90, 0, -90);
    auto right = new RigidBody(0, rightPosition, Quaternion::EulerInDegreesToQuaternion(rightEulerRotation), RigidBody::ShapeType::Plan, rightDimension);
    right->SetName("Right");
    EngineManager::getInstance().getScene()->addObject(*right);
    // Front
    Vector3 frontDimension = groundDimension;
    Vector3 frontPosition(0, 200, -200);
    Vector3 frontEulerRotation(-90, 0, 0);
    auto front = new RigidBody(0, frontPosition, Quaternion::EulerInDegreesToQuaternion(frontEulerRotation), RigidBody::ShapeType::Plan, frontDimension);
    front->SetName("Front");
    EngineManager::getInstance().getScene()->addObject(*front);
    // Back (without draw)
    Vector3 backDimension = groundDimension;
    Vector3 backPosition(0, 200, 200);
    Vector3 backEulerRotation(90, 0, 0);
    auto back = new RigidBody(0, backPosition, Quaternion::EulerInDegreesToQuaternion(backEulerRotation), RigidBody::ShapeType::Plan, backDimension);
    back->SetName("Back");
    EngineManager::getInstance().getScene()->addObject(*back);
    // ===========================================


    std::vector<RigidBody*>* allObjectsWithoutWalls = new std::vector<RigidBody*>();

    // ==================== forces + get all obj without plans ====================
    Gravity* gravityGenerator = new Gravity();
    // Add gravity force on each objects of the scene
    for (int i = 0; i<EngineManager::getInstance().getScene()->getObjects()->size(); i++) {
        auto obj = EngineManager::getInstance().getScene()->GetObject(i);
        if(obj->GetShapeType() != RigidBody::ShapeType::Plan) {
            // =============== gravity================
            EngineManager::getInstance().getPhysicEngine()->getForceRegistry()->Add(obj, gravityGenerator);
            allObjectsWithoutWalls->push_back(obj);
        }
    }

    // ==================== contacts ====================
    // contact avec le ground
    GroundContactGenerator* groundContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, groundPosition.GetY(),false, Vector3(0,1,0));// contact avec le sol à la meme hauteur que renseigné précédemment
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(groundContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le top
    GroundContactGenerator* topContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, topPosition.GetY(), true, Vector3(0,1,0));// contact avec le top à la meme hauteur que renseigné précédemment
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(topContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le left
    GroundContactGenerator* leftContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, leftPosition.GetX(), false, Vector3(1,0,0));// contact avec le left à la meme hauteur que renseigné précédemment
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(leftContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le right
    GroundContactGenerator* rightContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, rightPosition.GetX(),true, Vector3(1,0,0));// contact avec le right à la meme hauteur que renseigné précédemment
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(rightContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le front
    GroundContactGenerator* frontContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, frontPosition.GetZ(),false, Vector3(0,0,1));// contact avec le front à la meme hauteur que renseigné précédemment
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(frontContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le back
    GroundContactGenerator* backContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, backPosition.GetZ(),true, Vector3(0,0,1));// contact avec le back à la meme hauteur que renseigné précédemment
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(backContactGenerator, allObjectsWithoutWalls->size());



    EngineManager::getInstance().console.logSuccess("Advanced collision detection demo has been generated\n");
}