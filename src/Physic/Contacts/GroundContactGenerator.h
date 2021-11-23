#pragma once

#include "ContactGenerator.h"
#include <vector>

class GroundContactGenerator :
    public ContactGenerator
{
private:
    // particles that could collide the wall
    std::vector<RigidBody*>* rigidBodies;

    float positionY;
    Vector3 normal;
    bool inverse;
public: 
    GroundContactGenerator(std::vector<RigidBody*>* rigidBodies, float positionY = 0, bool inverse = false, Vector3 normal = Vector3(0,1,0));
    ~GroundContactGenerator();

    // Fill ParticleContact with information form particles and contact generator.
    // Contact is different wether the disitance is shaorter or greater than the length
    unsigned int addContact(std::vector<Contact*>* contacts, unsigned int limit) const override;
};

