#include "Scene.h"

Scene::Scene() {
    this->cam = new Camera(200, -35,0); // create main camera
    this->cam->setBackground(0.3f, 0.3f, 0.3f, 1.0f);

    this->objects = new std::vector<Object*>();
}

Scene::~Scene() {
    delete this->cam;
    delete this->objects;
}

std::vector<Object *> *Scene::getObjects() {
    return this->objects;
}

std::vector<Object *> Scene::getObjectsByCopy() const {
    return *this->objects;
}

Camera *Scene::getCamera() {
    return this->cam;
}

void Scene::addObject(Object &object) {
    this->objects->push_back(&object);
    EngineManager::getInstance().console.logSuccess("Add %s %d: %s\n", typeid(object).name(), this->objects->size(),object.body->toString().c_str());

}

Object *Scene::GetObject(int id) {
    if (id >= 0 && id < this->objects->size())
        return this->objects->at(id);
    else
        return nullptr;
}


void Scene::draw() {
    // Update Camera
    this->cam->Update();

    OpenGLRendererManager::drawPlan(10.0f, 10);
    OpenGLRendererManager::drawAxis(10);

    this->drawObjects();

}

void Scene::drawObjects() {
    for (auto &object : this->getObjectsByCopy()) // Browse objects
    {
        Vector3 pos = object->body->GetPosition(); // Get position
        Vector3 rot = object->body->GetOrientation().ToEulerInDegrees();
        switch(object->body->GetShapeType()){
            case RigidBody::ShapeType::Sphere :
                OpenGLRendererManager::drawSphere(object->body->GetDimensions(), object->body->GetPosition(), object->body->GetTransform(), rot); // create a small sphere to simulate object in 3D
                break;
            case RigidBody::ShapeType::Cube:
                OpenGLRendererManager::drawCube(object->body->GetDimensions(), object->body->GetPosition(), object->body->GetTransform(), rot); // create a small Cube to simulate object in 3D
                break;
            case RigidBody::ShapeType::Plan:
                OpenGLRendererManager::drawRect2D(object->body->GetDimensions(), object->body->GetPosition(), object->body->GetTransform()); // create a plan
                break;
            default:// draw sphere by default
                OpenGLRendererManager::drawSphere(object->body->GetDimensions(), object->body->GetPosition(), object->body->GetTransform(), rot); // create a small sphere to simulate object in 3D
                break;
        }
    }
}

void Scene::reset() {
    // delete objects
    for (auto object : *this->objects)
    {
        delete object;
    }
    this->objects->clear();
    EngineManager::getInstance().console.logSuccess("The scene has been cleaned\n");
}
