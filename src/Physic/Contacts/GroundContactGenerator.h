#pragma once

#include "ContactGenerator.h"
#include <vector>

class GroundContactGenerator :
    public ContactGenerator
{
private:
    // objects that could collide the wall
    std::vector<RigidBody*>* rigidBodies;

    float positionY;
    Vector3 normal;
    bool inverse;
public: 
    GroundContactGenerator(std::vector<RigidBody*>* rigidBodies, float positionY = 0, bool inverse = false, Vector3 normal = Vector3(0,1,0));
    ~GroundContactGenerator();

    // Fill Contact with information form objects and contact generator.
    // Contact is different wether the distance is shorter or greater than the length
    unsigned int addContact(std::vector<Contact*>* contacts, unsigned int limit) const override;
};

