#pragma once

#include "../Contacts/Contact.h"
#include <vector>

class CollisionData
{
public:
    std::vector<Contact*>* contacts;

    bool hasMoreContacts();

    void reset();

    void addContact(Contact *contact);


    std::string toString() const;

    // << operator
    friend std::ostream& operator << (std::ostream& os, const CollisionData& collisionData);
};