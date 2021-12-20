#include "AdvancedCollisionDetection.h"


void AdvancedCollisionDetection::GenerateScene()
{
    // clear all objects added in the scene
    EngineManager::getInstance().getScene()->reset();


    float mass = 50.f;
    Vector3 boiteDimension(10, 10, 10);
    // boite
    Vector3 boitePosition(-165, boiteDimension.GetMaxValue()+5, 0);
    Vector3 boiteEulerRotation(0, 0, 0);
    Vector3 boiteVelocity(500.f, 500.f, 0.f);
    Vector3 boiteAngularVelocity(1.f, 1.f, 1.50f);
    auto box = new Box(boitePosition, boiteDimension);
    box->setBody(new RigidBody(mass, boitePosition,boiteVelocity, Quaternion::EulerInDegreesToQuaternion(boiteEulerRotation), boiteAngularVelocity, RigidBody::ShapeType::Cube, boiteDimension));
    box->body->SetName(u8"Boite");
    EngineManager::getInstance().getScene()->addObject(*box);


    // ================ walls =================
    // Ground
    Vector3 groundDimension(200, 0, 200);
    Vector3 groundPosition(0, -0, 0);
    Vector3 groundEulerRotation(0, 0, 0);
    auto ground = new Plane(Vector3(0,1,0), groundPosition.GetY(), groundPosition, groundDimension);//new Plane();
    ground->setBody(new RigidBody(0, groundPosition, Quaternion::EulerInDegreesToQuaternion(groundEulerRotation), RigidBody::ShapeType::Plan, groundDimension));
    ground->body->SetName("Ground");
    EngineManager::getInstance().getScene()->addObject(*ground);
    // Left
    Vector3 leftDimension = groundDimension;
    Vector3 leftPosition(-200, 200, 0);
    Vector3 leftEulerRotation(90, 0, 90);
    auto left = new Plane(Vector3(1,0,0), leftPosition.GetX(), leftPosition, leftDimension);//new Plane();
    left->setBody(new RigidBody(0, leftPosition, Quaternion::EulerInDegreesToQuaternion(leftEulerRotation), RigidBody::ShapeType::Plan, leftDimension));
    left->body->SetName("Left");
    EngineManager::getInstance().getScene()->addObject(*left);
    // Right
    Vector3 rightDimension = groundDimension;
    Vector3 rightPosition(200, 200, 0);
    Vector3 rightEulerRotation(90, 0, -90);
    auto right = new Plane(Vector3(-1,0,0), rightPosition.GetX(), rightPosition, rightDimension);//new Plane();
    right->setBody(new RigidBody(0, rightPosition, Quaternion::EulerInDegreesToQuaternion(rightEulerRotation), RigidBody::ShapeType::Plan, rightDimension));
    right->body->SetName("Right");
    EngineManager::getInstance().getScene()->addObject(*right);
    // Top
    Vector3 topDimension = groundDimension;
    Vector3 topPosition(0, 400, 0);
    Vector3 topEulerRotation(180, 0, 0);
    auto top = new Plane(Vector3(0,-1,0), topPosition.GetY(), topPosition, topDimension);//new Plane();
    top->setBody(new RigidBody(0, topPosition, Quaternion::EulerInDegreesToQuaternion(topEulerRotation), RigidBody::ShapeType::Plan, topDimension));
    top->body->SetName("Top");
    EngineManager::getInstance().getScene()->addObject(*top);
    // Front
    Vector3 frontDimension = groundDimension;
    Vector3 frontPosition(0, 200, -200);
    Vector3 frontEulerRotation(-90, 0, 0);
    auto front = new Plane(Vector3(0,0,1), frontPosition.GetZ(), frontPosition, frontDimension);//new Plane();
    front->setBody(new RigidBody(0, frontPosition, Quaternion::EulerInDegreesToQuaternion(frontEulerRotation), RigidBody::ShapeType::Plan, frontDimension));
    front->body->SetName("Front");
    EngineManager::getInstance().getScene()->addObject(*front);
    // Back (without draw)
    Vector3 backDimension = groundDimension;
    Vector3 backPosition(0, 200, 200);
    Vector3 backEulerRotation(90, 0, 0);
    auto back = new Plane(Vector3(0,0,-1), backPosition.GetZ(), backPosition, backDimension);//new Plane();
    back->setBody(new RigidBody(0, backPosition, Quaternion::EulerInDegreesToQuaternion(backEulerRotation), RigidBody::ShapeType::Plan, backDimension));
    back->body->SetName("Back");
    EngineManager::getInstance().getScene()->addObject(*back);
    // ===========================================

    // TODO: add node to BVH

    std::vector<Object*>* allObjectsWithoutWalls = new std::vector<Object*>();

    // ==================== gravity ====================
    Gravity* gravityGenerator = new Gravity();
    // Add gravity force on box
    EngineManager::getInstance().getPhysicEngine()->getForceRegistry()->Add(box->body, gravityGenerator);
    allObjectsWithoutWalls->push_back(box);


    EngineManager::getInstance().console.logSuccess("Advanced collision detection demo has been generated\n");
}