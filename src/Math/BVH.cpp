#include "BVH.h"

Node::Node() {
    this->parentNode = nullptr;
    this->primitive = nullptr;
    this->sphere = BoundingSphere();
    this->childNodes = std::vector<Node *>();
}

Node::Node(Primitive* _primitive) {
    this->parentNode = nullptr;
    this->primitive = _primitive;

    this->sphere = BoundingSphere(this->primitive->getCenter(), this->primitive->body->GetDimensions().GetMaxValue());
    this->childNodes = std::vector<Node *>();
}


Node::Node(Node* parent, const BoundingSphere &sphere, Primitive* _primitive) {
    this->parentNode = parent;
    this->primitive = _primitive;
    this->sphere = sphere;
    this->childNodes = std::vector<Node *>();
}

float Node::getSphereVolume() {
    return (4.f / 3.f) * M_PI * powf(sphere.radius, 2);
}

BoundingSphere Node::sphereBouding2Nodes(BoundingSphere sphereA, BoundingSphere sphereB) {
    BoundingSphere newSphere;

    float distanceAB = (sphereB.center - sphereA.center).Magnitude();
    // si l'une des 2 sphères englobe l'autre
    if (distanceAB < sphereA.radius + sphereB.radius) {
        newSphere.radius = sphereA.radius > sphereB.radius ? sphereA.radius : sphereB.radius;
        newSphere.center = sphereA.radius > sphereB.radius ? sphereA.center : sphereB.center;
    } else {
        if (distanceAB != 0) {
            // on récupère les extrémités du diamètre englobant
            Vector3 norm = (sphereB.center - sphereA.center).Normalize();

            Vector3 segmentCoteA = sphereA.center - norm * sphereA.radius;
            Vector3 segmentCoteB = sphereB.center + norm * sphereB.radius;

            newSphere.center = (segmentCoteA + segmentCoteB) / 2.0f;
            // le rayon équivaut maintenant à la moitié du diamètre englobant
            newSphere.radius = (segmentCoteA - segmentCoteB).Magnitude() / 2.f;
        } else {
            // si les 2 nodes ont la meme position, on prend le plus grand rayon
            newSphere.radius = sphereA.radius > sphereB.radius ? sphereA.radius : sphereB.radius;
            newSphere.center = sphereA.radius > sphereB.radius ? sphereA.center : sphereB.center;

        }
    }
    return newSphere;
}

Node* Node::getBrotherNode() {
    Node *brother = nullptr;
    if (hasParent()) {
        int sizeParentChilds = this->parentNode->childNodes.size();
        int i = 0;
        while (i < sizeParentChilds && brother == nullptr) {
            if (this->parentNode->childNodes[i] != this && brother == nullptr) {
                brother = this->parentNode->childNodes[i];
            }
        }
    }

    return brother;
}

void Node::RemoveFromChild(Node* node) {
    int index = 0;
    int indexNodeToRemove = -1;

    for (Node *child: this->childNodes) {
        if (child == node) {
            indexNodeToRemove = index;
        }
        index++;
    }

    if (indexNodeToRemove == -1) {
        std::cout << "Node not found" << std::endl;
        return;
    }

    this->childNodes.erase(this->childNodes.begin() + indexNodeToRemove);

}

void Node::insertNode(Primitive* newPrimitive, const BoundingSphere &newSphere) {
    // If we are a leaf, then the only option is to spawn two
    // new children and place the new primitive in one.
    if (isLeaf()) {
        // Child one is a copy of us.
        this->childNodes.push_back(new Node(
                this, this->sphere, this->primitive
        ));

        // Child two holds the new primitive
        this->childNodes.push_back(new Node(
                this, newSphere, newPrimitive
        ));

        // And we now loose the primitive (we're no longer a leaf)
        this->primitive = nullptr;

        // We need to recalculate our bounding volume
        this->recalculateBoundingVolume();
    }

    // Otherwise we need to work out which child gets to keep
    // the inserted primitive. We give it to whoever would grow the
    // least to incorporate it.
    else {
        if (this->childNodes.size() == 2) {
            if (this->childNodes[0]->sphere.getGrowth(newSphere) <
                this->childNodes[1]->sphere.getGrowth(newSphere)) {
                this->childNodes[0]->insertNode(newPrimitive, newSphere);
            } else {
                this->childNodes[1]->insertNode(newPrimitive, newSphere);
            }
        } else if (this->childNodes.size() == 1) {
            if (this->childNodes[0]->sphere.getGrowth(newSphere) >
                this->sphere.getGrowth(newSphere)) {
                this->childNodes[0]->insertNode(newPrimitive, newSphere);
            } else {
                this->childNodes.push_back(new Node(this, newSphere, newPrimitive));
            }
        } else {
            this->childNodes.push_back(new Node(this, newSphere, newPrimitive));
        }
        // We need to recalculate our bounding volume to be sure
        this->recalculateBoundingVolume();

    }
}

void Node::deleteNode() {
    if (hasParent() && this->parentNode->childNodes.size() == 2) {
        Node *grandParent = this->parentNode->parentNode;
        Node *parent = this->parentNode;
        Node *brother = getBrotherNode();

        grandParent->RemoveFromChild(parent);

        brother->parentNode = grandParent;
        grandParent->childNodes.push_back(brother);
    }

    delete this;
}

void Node::print(int degree) {
    std::cout << "|";
    for (int i = 0; i < degree; i++) {
        std::cout << "----";
    }

    std::cout << "Node (nb child: " << this->childNodes.size() << ") center:" << this->sphere.center << " rayon:" << this->sphere.radius << " ";
    if (isLeaf())
        std::cout << "   >>>    " << this->primitive->body->GetName() << ": primitive.center:" << *this->primitive->center;
    std::cout << " \n";

    for (Node *child: this->childNodes) {
        child->print(degree + 1);
    }
}

const Primitive& Node::getPrimitive() const {
    return *this->primitive;
}

BVH::BVH() {
    root = new Node();
}

void BVH::broadPhaseCheck(Node* parent, CollisionData* cd) {
    if (parent->childNodes.size() == 2) {
        Node *child1 = parent->childNodes[0];
        Node *child2 = parent->childNodes[1];

        broadPhaseCheckChildPrimitive(child1, child2, cd);
    }
}


void BVH::broadPhaseCheckChildPrimitive(Node *child1, Node *child2, CollisionData* cd) {
    // Early out if we don't overlap
    if (!child1->sphere.overlaps(child2->sphere)) return;

    // If we're both at leaf nodes, then we have a potential contact
    if (child1->isLeaf() && child2->isLeaf()) {
        if (child1->primitive->body->GetShapeType() == RigidBody::ShapeType::Sphere &&
            child2->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan) {
            CollisionDetector::sphereAndHalfSpace((const Sphere &) child1->getPrimitive(),
                                                  (const Plane &) child2->getPrimitive(),
                                                  cd);
        } else if (child1->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan &&
                   child2->primitive->body->GetShapeType() == RigidBody::ShapeType::Sphere) {
            CollisionDetector::sphereAndHalfSpace((const Sphere &) child2->getPrimitive(),
                                                  (const Plane &) child1->getPrimitive(),
                                                  cd);
        } else if (child1->primitive->body->GetShapeType() == RigidBody::ShapeType::Cube &&
                   child2->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan) {
            CollisionDetector::boxAndHalfSpace((const Box &) child1->getPrimitive(),
                                               (const Plane &) child2->getPrimitive(),
                                               cd);
        } else if (child1->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan &&
                   child2->primitive->body->GetShapeType() == RigidBody::ShapeType::Cube) {
            CollisionDetector::boxAndHalfSpace((const Box &) child2->getPrimitive(),
                                               (const Plane &) child1->getPrimitive(),
                                               cd);
        }
    }
    // If one of use is not at leaf node, then we check childrens
    if (!child1->isLeaf() && child2->isLeaf()) {
        if (child1->sphere.getVolume() >= child2->sphere.getVolume()) {
            broadPhaseCheckChildPrimitive(child1->childNodes[0],
                                          child2, cd
            );
            broadPhaseCheckChildPrimitive(child1->childNodes[1],
                                          child2, cd
            );
        }
    } else if (child1->isLeaf() && !child2->isLeaf()) {
        if (child1->sphere.getVolume() >= child2->sphere.getVolume()) {
            broadPhaseCheckChildPrimitive(child1,
                                          child2->childNodes[0], cd
            );
            broadPhaseCheckChildPrimitive(child1,
                                          child2->childNodes[1], cd
            );
        }
    }
        // if both are not at leaf nodes, we check all childrens
    else if (!child1->isLeaf() && !child2->isLeaf()) {
        for (Node *child_1: child1->childNodes) {
            for (Node *child_2: child2->childNodes) {
                broadPhaseCheckChildPrimitive(child_1, child_2, cd);
            }
        }
    }

    // if we have children, check them 2 by 2
    if (child1->childNodes.size() > 0) {
        broadPhaseCheckChildPrimitive(child1->childNodes[0], child1->childNodes[1], cd);
    }
    if (child2->childNodes.size() > 0) {
        broadPhaseCheckChildPrimitive(child2->childNodes[0], child2->childNodes[1], cd);
    }
}


void BVH::broadPhaseCheck(CollisionData* cd) {
    //CollisionData* cd = new CollisionData();
    broadPhaseCheck(this->root, cd);
}

void BVH::insertNode(Node* node) {
    root->insertNode(node->primitive, node->sphere);
}

void BVH::print() {
    std::cout << "==============" << std::endl;
    root->print(0);
    std::cout << "==============" << std::endl;
}

void Node::recalculateBoundingVolume() {
    if (isLeaf()) return;

    if (this->childNodes.size() == 2) {
        // Use the bounding volume combining constructor.
        this->sphere = BoundingSphere(
                this->childNodes[0]->sphere,
                this->childNodes[1]->sphere
        );
    } else if (this->childNodes.size() == 1) {
        // use the only child characteristics
        this->sphere = this->childNodes[0]->sphere;
    }

    // Recurse up the tree
    if (this->parentNode) this->parentNode->recalculateBoundingVolume();
}
