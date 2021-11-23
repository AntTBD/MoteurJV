#include "CarCollision.h"

void CarCollision::GenerateScene()
{
    // clear all objects add in the scene
    EngineManager::getInstance().getScene()->reset();


    std::vector<RigidBody*>* cars = new std::vector<RigidBody*>();

    float mass = 50.f;
    Vector3 carDimension(15, 5, 10);
    Vector3 feuDimension(2.5f, 2.5f, 2.5f);

    // ================ cars =================
    // car1
    Vector3 positionCar1(-165, carDimension.GetMaxValue()+5, 0);
    Vector3 eulerRotationCar1(0, 0, 0);
    Vector3 velocityCar1(500.f, 0.f, 0.f);
    Vector3 angularVelocityCar1(0.f, 0.f, 0.0f);
    cars->push_back(new RigidBody(mass, positionCar1,velocityCar1, Quaternion::EulerInDegreesToQuaternion(eulerRotationCar1), angularVelocityCar1, RigidBody::ShapeType::Cube, carDimension));
    //cars->push_back(new RigidBody(mass, positionCar1, RigidBody::ShapeType::Cube, carDimension));
    cars->at(cars->size()-1)->SetName("Car1");
    cars->at(cars->size()-1)->AddForceAtBodyPoint(Vector3(1500.f, 0.f, 0.f), Vector3(-carDimension.GetX(), -carDimension.GetY(), 0));
    EngineManager::getInstance().getScene()->addObject(*cars->at(cars->size()-1));
    /*// feu droit
    Vector3 feuDroit1(carDimension.GetX(), 0, carDimension.GetZ()-5);
    feuDroit1 = cars->at(0)->GetPointInWorldSpace(feuDroit1);
    cars->push_back(new RigidBody(mass, feuDroit1, RigidBody::ShapeType::Sphere, feuDimension));
    cars->at(cars->size()-1)->SetName("FeuDroit1");
    EngineManager::getInstance().getScene()->addObject(*cars->at(cars->size()-1));
    // feu gauche
    Vector3 feuGauche1(carDimension.GetX(), 0, -carDimension.GetZ()+5);
    feuGauche1 = cars->at(0)->GetPointInWorldSpace(feuGauche1);
    cars->push_back(new RigidBody(mass, feuGauche1, RigidBody::ShapeType::Sphere, feuDimension));
    cars->at(cars->size()-1)->SetName("FeuGauche1");
    EngineManager::getInstance().getScene()->addObject(*cars->at(cars->size()-1));
*/
    // car2
    Vector3 positionCar2(165, carDimension.GetMaxValue(), 0);
    Vector3 eulerRotationCar2(0, 180, 0);
    Vector3 velocityCar2(-500.f, 0.f, 0.f);
    Vector3 angularVelocityCar2(0.f, 0.f, 0.0f);
    cars->push_back(new RigidBody(mass, positionCar2, velocityCar2, Quaternion::EulerInDegreesToQuaternion(eulerRotationCar2), angularVelocityCar2, RigidBody::ShapeType::Cube, carDimension));
    //cars->push_back(new RigidBody(mass, positionCar2, RigidBody::ShapeType::Cube, carDimension));
    cars->at(cars->size()-1)->SetName("Car2");
    cars->at(cars->size()-1)->AddForceAtBodyPoint(Vector3(-1500.f, 0.f, 0.f), Vector3(carDimension.GetX(), -carDimension.GetY(), 0));
    EngineManager::getInstance().getScene()->addObject(*cars->at(cars->size()-1));
    // ================ =======================

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

    // ==================== forces ====================
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
    /*ParticleSpring *particleSpringGenerator = new ParticleSpring(*allObjectsWithoutWalls->at(0), 5, carDimension.GetMaxValue()*2.f);
    // Add spring force
    EngineManager::getInstance().getPhysicEngine()->getForceRegistry()->Add(allObjectsWithoutWalls->at(1), particleSpringGenerator);
    */
    // ==================== contacts ====================
    // ------ add contacts -------
    // add contacts naive entre chaque objets (=colision entre 2 particules)
    NaiveContactGenerator *naiveContactGenerator = new NaiveContactGenerator(allObjectsWithoutWalls);// contacts entre particules de rayon 10
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(naiveContactGenerator, 2 * allObjectsWithoutWalls->size());
    /*NaiveParticleContactGenerator *naiveParticleContactGenerator1 = new NaiveParticleContactGenerator( new std::vector<RigidBody*>({cars->at(0), cars->at(3)}) );
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(naiveParticleContactGenerator1, 2 * 2);
    NaiveParticleContactGenerator *naiveParticleContactGenerator2 = new NaiveParticleContactGenerator( new std::vector<RigidBody*>({cars->at(1), cars->at(3)}) );
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(naiveParticleContactGenerator2, 2 * 2);
    NaiveParticleContactGenerator *naiveParticleContactGenerator3 = new NaiveParticleContactGenerator( new std::vector<RigidBody*>({cars->at(2), cars->at(3)}) );
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(naiveParticleContactGenerator3, 2 * 2);

    auto tige = new ParticleRod(cars->at(0), cars->at(1), (cars->at(1)->GetPosition()-cars->at(0)->GetPosition()).Magnitude());// tige de longueur 200
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(tige, 1);
    tige = new ParticleRod(cars->at(0), cars->at(2), (cars->at(2)->GetPosition()-cars->at(0)->GetPosition()).Magnitude());// tige de longueur 200
    EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(tige, 1);*/

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
