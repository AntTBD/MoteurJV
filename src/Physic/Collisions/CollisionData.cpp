#include "CollisionData.h"


CollisionData::CollisionData(){
    this->contacts = new std::vector<Contact*>();
}
CollisionData::~CollisionData(){
    this->contacts = nullptr;
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
    os << "==== Collision Data ====\n" << "All Collisions : (" << collisionData.contacts->size() << ")\n";

    for (Contact *contact : *collisionData.contacts) {
        os << "-- CONTACT --\n"
            << "object(s) : \n";
        if(contact->m_rigidBody[0] != nullptr)
            os << contact->m_rigidBody[0]->toString() << "\n";
        if(contact->m_rigidBody[1] != nullptr)
            os << contact->m_rigidBody[1]->toString() << "\n";
        os << "infos : \n"
            << "- normal : " << contact->m_contactNormal << "\n"
            << "- point de contact : " << contact->m_contactPoint << "\n"
            << "- penetration : " << contact->m_penetration << "\n"
            << "- restitution : " << contact->m_restitution << "\n"
            << "\n";
    }

    return os;
}