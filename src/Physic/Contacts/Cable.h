#pragma once

#include "Link.h"

class Cable :
    public Link
{
public:

    // a contact will be generated if the distance
    // between objects is larger than maxlength
    float maxLength;

    // float bounciness of the cable
    float restitution;

    Cable(RigidBody* rigidBody1, RigidBody* rigidBody2, float maxLength);
    ~Cable();

    // Fill Contact ith information from objects and contact generator
    unsigned int addContact(std::vector<Contact*>* contacts, unsigned int limit) const override;
};

