#pragma once

#include "../Contacts/Contact.h"
#include <vector>

class CollisionData {
public:
    std::vector<Contact *> *contacts;

    CollisionData();

    ~CollisionData();

    void addContact(Contact *contact);

    std::string toString() const;

    // << operator
    friend std::ostream &operator<<(std::ostream &os, const CollisionData &collisionData);
};