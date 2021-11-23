#pragma once

#include "ParticleLink.h"

class Cable :
    public ParticleLink
{
public:

    // a contact will be generated if the distance
    // between particles is larger than maxlength
    float maxLength;

    // float bounciness of the cable
    float restitution;

    Cable(RigidBody* rigidBody1, RigidBody* rigidBody2, float maxLength);
    ~Cable();

    // Fill ParticleContact ith information from particles and contact generator
    unsigned int addContact(std::vector<ParticleContact*>* contacts, unsigned int limit) const override;
};

