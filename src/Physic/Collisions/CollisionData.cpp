#include "CollisionData.h"


bool CollisionData::hasMoreContacts()
{
    return contacts->size() > 0;
}

void CollisionData::reset()
{
    contacts->clear();
}

void CollisionData::addContact(Contact *contact)
{
    contacts->push_back(contact);
}


std::string CollisionData::toString() const {
    std::stringstream stream;
    stream << *this;
    return stream.str();
}

std::ostream &operator<<(std::ostream &os, const CollisionData &collisionData) {
    os << "==== Collision Data ====\n" << "All Collisions : \n";

    for (Contact *contact : *collisionData.contacts) {
        os << "-- CONTACT --\n"
            << "object(s) : \n";
        if(contact->m_rigidBody[0] != nullptr)
            os << contact->m_rigidBody[0]->toString() << "\n";
        if(contact->m_rigidBody[1] != nullptr)
            os << contact->m_rigidBody[1]->toString() << "\n";
        os << "infos : \n"
            << "normal : " << contact->m_contactNormal.toString()
            << "penetration : " << contact->m_penetration
            << "restitution : " << contact->m_restitution
            << "\n";
    }

    return os;
}