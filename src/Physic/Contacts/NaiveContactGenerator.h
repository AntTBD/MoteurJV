#pragma once

#include "ContactGenerator.h"
#include <vector>

class NaiveContactGenerator :
    public ContactGenerator
{
public:
    // Object radius
    float radius;

    // objects that could collide together
    std::vector<RigidBody*>* rigidBodies;

    NaiveContactGenerator(std::vector<RigidBody*>* RigidBodies, float radius = 10);
    ~NaiveContactGenerator();

    // iterate throught every pair of objects to check their penetration
    unsigned int addContact(std::vector<Contact*>* contacts, unsigned int limit) const override;
};

