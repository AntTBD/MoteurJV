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
    auto box = new Box(boitePosition, boiteDimension);
    box->setBody(new RigidBody(mass, boitePosition,boiteVelocity, Quaternion::EulerInDegreesToQuaternion(boiteEulerRotation), boiteAngularVelocity, RigidBody::ShapeType::Cube, boiteDimension));
    box->body->SetName(u8"Bo�te");
    EngineManager::getInstance().getScene()->addObject(*box);


    // ================ walls =================
    // Ground
    Vector3 groundDimension(200, 10, 200);
    Vector3 groundPosition(0, -0, 0);
    Vector3 groundEulerRotation(0, 0, 0);
    auto ground = new Box(groundPosition, groundDimension);//new Plane(Vector3(0,1,0), groundPosition.GetY());
    ground->setBody(new RigidBody(0, groundPosition, Quaternion::EulerInDegreesToQuaternion(groundEulerRotation), RigidBody::ShapeType::Cube, groundDimension));
    ground->body->SetName("Ground");
    EngineManager::getInstance().getScene()->addObject(*ground);
    // Top
    Vector3 topDimension = groundDimension;
    Vector3 topPosition(0, 400, 0);
    Vector3 topEulerRotation(180, 0, 0);
    auto top = new Box(topPosition, topDimension);//new Plane(Vector3(0,1,0), groundPosition.GetY());
    top->setBody(new RigidBody(0, topPosition, Quaternion::EulerInDegreesToQuaternion(topEulerRotation), RigidBody::ShapeType::Cube, topDimension));
    top->body->SetName("Top");
    EngineManager::getInstance().getScene()->addObject(*top);
    // Left
    Vector3 leftDimension = groundDimension;
    Vector3 leftPosition(-200, 200, 0);
    Vector3 leftEulerRotation(90, 0, 90);
    auto left = new Box(leftPosition, leftDimension);//new Plane(Vector3(1,0,0), groundPosition.GetX());
    left->setBody(new RigidBody(0, leftPosition, Quaternion::EulerInDegreesToQuaternion(leftEulerRotation), RigidBody::ShapeType::Cube, leftDimension));
    left->body->SetName("Left");
    EngineManager::getInstance().getScene()->addObject(*left);
    // Right
    Vector3 rightDimension = groundDimension;
    Vector3 rightPosition(200, 200, 0);
    Vector3 rightEulerRotation(90, 0, -90);
    auto right = new Box(rightPosition, rightDimension);//new Plane(Vector3(1,0,0), groundPosition.GetX());
    right->setBody(new RigidBody(0, rightPosition, Quaternion::EulerInDegreesToQuaternion(rightEulerRotation), RigidBody::ShapeType::Cube, rightDimension));
    right->body->SetName("Right");
    EngineManager::getInstance().getScene()->addObject(*right);
    // Front
    Vector3 frontDimension = groundDimension;
    Vector3 frontPosition(0, 200, -200);
    Vector3 frontEulerRotation(-90, 0, 0);
    auto front = new Box(frontPosition, frontDimension);//new Plane(Vector3(0,0,1), groundPosition.GetZ());
    front->setBody(new RigidBody(0, frontPosition, Quaternion::EulerInDegreesToQuaternion(frontEulerRotation), RigidBody::ShapeType::Cube, frontDimension));
    front->body->SetName("Front");
    EngineManager::getInstance().getScene()->addObject(*front);
    // Back (without draw)
    Vector3 backDimension = groundDimension;
    Vector3 backPosition(0, 200, 200);
    Vector3 backEulerRotation(90, 0, 0);
    auto back = new Box(backPosition, backDimension);//new Plane(Vector3(0,0,1), groundPosition.GetZ());
    back->setBody(new RigidBody(0, backPosition, Quaternion::EulerInDegreesToQuaternion(backEulerRotation), RigidBody::ShapeType::Cube, backDimension));
    back->body->SetName("Back");
    EngineManager::getInstance().getScene()->addObject(*back);
    // ===========================================

    // TODO: add node to BVH

    std::vector<Object*>* allObjectsWithoutWalls = new std::vector<Object*>();

    // ==================== forces + get all obj without plans ====================
    Gravity* gravityGenerator = new Gravity();
    // Add gravity force on each objects of the scene
    for (int i = 0; i<EngineManager::getInstance().getScene()->getObjects()->size(); i++) {
        auto obj = EngineManager::getInstance().getScene()->GetObject(i);
        if(obj->body->GetShapeType() != RigidBody::ShapeType::Plan) {
            // =============== gravity================
            EngineManager::getInstance().getPhysicEngine()->getForceRegistry()->Add(obj->body, gravityGenerator);
            allObjectsWithoutWalls->push_back(obj);
        }
    }

    // ==================== contacts ====================
    /*// contact avec le ground
    GroundContactGenerator* groundContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, groundPosition.GetY(),false, Vector3(0,1,0));// contact avec le sol � la meme hauteur que renseign� pr�c�demment
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(groundContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le top
    GroundContactGenerator* topContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, topPosition.GetY(), true, Vector3(0,1,0));// contact avec le top � la meme hauteur que renseign� pr�c�demment
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(topContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le left
    GroundContactGenerator* leftContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, leftPosition.GetX(), false, Vector3(1,0,0));// contact avec le left � la meme hauteur que renseign� pr�c�demment
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(leftContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le right
    GroundContactGenerator* rightContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, rightPosition.GetX(),true, Vector3(1,0,0));// contact avec le right � la meme hauteur que renseign� pr�c�demment
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(rightContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le front
    GroundContactGenerator* frontContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, frontPosition.GetZ(),false, Vector3(0,0,1));// contact avec le front � la meme hauteur que renseign� pr�c�demment
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(frontContactGenerator, allObjectsWithoutWalls->size());
    // contact avec le back
    GroundContactGenerator* backContactGenerator = new GroundContactGenerator(allObjectsWithoutWalls, backPosition.GetZ(),true, Vector3(0,0,1));// contact avec le back � la meme hauteur que renseign� pr�c�demment
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(backContactGenerator, allObjectsWithoutWalls->size());
*/


    EngineManager::getInstance().console.logSuccess("Advanced collision detection demo has been generated\n");
}