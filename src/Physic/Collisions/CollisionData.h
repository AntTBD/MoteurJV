#pragma once

#include "../Contacts/Contact.h"
#include <vector>

class CollisionData
{
public:
    std::vector<Contact*>* contacts;

    void addContact(Contact *contact);

    //void generateContact(primitive1, primitive2);


    std::string toString() const;

    // << operator
    friend std::ostream& operator << (std::ostream& os, const CollisionData& collisionData);
};