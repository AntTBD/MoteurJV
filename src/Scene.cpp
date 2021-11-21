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
    for (auto &object : this->getObjectsByCopy()) // Browse particles
    {
        Vector3 pos = object->GetPosition(); // Get position
        Vector3 rot = object->GetOrientation().ToEulerInDegrees();
        switch(object->GetShapeType()){
            case RigidBody::ShapeType::Sphere :
                OpenGLRendererManager::drawSphere(object->GetDimensions(), object->GetPosition(), object->GetTransform(), rot); // create a small sphere to simulate particle in 3D
                break;
            case RigidBody::ShapeType::Cube:
                OpenGLRendererManager::drawCube(object->GetDimensions(), object->GetPosition(), object->GetTransform(), rot); // create a small Cube to simulate particle in 3D
                break;
            case RigidBody::ShapeType::Plan:
                OpenGLRendererManager::drawRect2D(object->GetDimensions(), object->GetPosition(), object->GetTransform()); // create a plan
                break;
            default:// draw sphere by default
                OpenGLRendererManager::drawSphere(object->GetDimensions(), object->GetPosition(), object->GetTransform(), rot); // create a small sphere to simulate particle in 3D
                break;
        }
    }
}

void Scene::reset() {
    // delete particles
    for (auto object : *this->objects)
    {
        delete object;
    }
    this->objects->clear();
}
