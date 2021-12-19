#include "BVH.h"

Node::Node()
{
	this->parentNode = nullptr;
    this->primitive = nullptr;
	this->sphere = BoundingSphere();
	this->sphere.center = Vector3();
	this->sphere.radius = 0;
    this->childNodes = std::vector<Node*>();
}

Node::Node(Primitive* _primitive)
{
	this->parentNode = nullptr;
	this->primitive = _primitive;

    this->sphere = BoundingSphere();
	sphere.center = this->primitive->getCenter();
	sphere.radius = this->primitive->body->GetDimensions().GetMaxValue();
    this->childNodes = std::vector<Node*>();
}

float Node::getSphereVolume()
{
	return  (4.f / 3.f) * 3.14f * sphere.radius * sphere.radius;
}

BoundingSphere Node::sphereBouding2Nodes(BoundingSphere sphereA, BoundingSphere sphereB)
{
	BoundingSphere newSphere;

    float distanceAB = (sphereA.center + sphereB.center).Magnitude();
    if(distanceAB < sphereA.radius + sphereB.radius || distanceAB == 0){
        newSphere.radius = sphereA.radius > sphereB.radius ? sphereA.radius : sphereB.radius;
        newSphere.center = sphereA.radius > sphereB.radius ? sphereA.center : sphereB.center;
    }else{
        if(distanceAB > 0) {
            Vector3 norm = (sphereB.center - sphereA.center).Normalize();

            Vector3 segmentCoteA = sphereA.center - norm * sphereA.radius;
            Vector3 segmentCoteB = sphereB.center + norm * sphereB.radius;

            newSphere.center = Vector3(
                    (segmentCoteA.GetX() + segmentCoteB.GetX()) / 2.f,
                    (segmentCoteA.GetY() + segmentCoteB.GetY()) / 2.f,
                    (segmentCoteA.GetZ() + segmentCoteB.GetZ()) / 2.f);
            newSphere.radius = (segmentCoteA - segmentCoteB).Magnitude() /2.f;
        }
    }
	return newSphere;
}

Node* Node::getBrotherNode()
{
	Node* brother = nullptr;
	if (hasParent())
	{
		int sizeParentChilds = this->parentNode->childNodes.size();
		int i = 0;
		while(i < sizeParentChilds && brother == nullptr)
		{
			if (this->parentNode->childNodes[i] != this && brother == nullptr) {
				brother = this->parentNode->childNodes[i];
			}
		}
	}

	return brother;
}

void Node::RemoveFromChild(Node* node)
{
	int index = 0;
	int indexNodeToRemove = -1;

	for (Node* child : this->childNodes)
	{
		if (child == node)
		{
			indexNodeToRemove = index;
		}
		index++;
	}

	if (indexNodeToRemove == -1)
	{
		std::cout << "Node not found" << std::endl;
		return;
	}

	this->childNodes.erase(this->childNodes.begin() + indexNodeToRemove);

}

void Node::insertNode(Node* node)
{
	if ( isLeaf())
	{
        // ce node devient le parent des 2 nouveaux enfants
        // on cré un nouvel enfant
        Node *newChild = new Node();
        // on transfert la primitive au nouvel enfant et on l'enlève dans notre noeud
        if(this->primitive != nullptr){
            newChild->primitive = this->primitive;
            this->primitive = nullptr;
        }
        newChild->sphere = this->sphere;
        // on clear les enfants
        this->childNodes.clear();
        // on redéfinit le parent des 2 nouveaux enfants
        node->parentNode = this;
        this->childNodes.push_back(node);
        newChild->parentNode = this;
        this->childNodes.push_back(newChild);
        // on recalcule la sphere englobante avec maintenant les 2 enfants
        this->sphere = this->sphereBouding2Nodes(newChild->sphere, node->sphere);

        //if(this->parentNode != nullptr)
        //    this->parentNode->sphere =  this->sphereBouding2Nodes(this->parentNode->childNodes.at(0)->sphere, this->parentNode->childNodes.at(1)->sphere);
        Node* tempNode = this;
        while(tempNode->parentNode != nullptr){
            tempNode->parentNode->sphere =  tempNode->sphereBouding2Nodes(tempNode->parentNode->childNodes.at(0)->sphere, tempNode->parentNode->childNodes.at(1)->sphere);
            tempNode = tempNode->parentNode;
        }
	}
	else
	{
		float minSearch = std::numeric_limits<float>::max();
		Node* childToSave = nullptr;
        BoundingSphere sphere;
		for (Node* child : this->childNodes)
		{
            sphere = this->sphereBouding2Nodes(child->sphere, node->sphere);

            if (sphere.radius < minSearch) {
                minSearch = sphere.radius;
                childToSave = child;
            }
		}
        if(childToSave != nullptr){
            childToSave->insertNode(node);
        }
	}
}

void Node::deleteNode()
{
	if (hasParent() && this->parentNode->childNodes.size() == 2)
	{
		Node* grandParent = this->parentNode->parentNode;
		Node* parent = this->parentNode;
		Node* brother = getBrotherNode();

		grandParent->RemoveFromChild(parent);

		brother->parentNode = grandParent;
		grandParent->childNodes.push_back(brother);
	}

	delete this;
}

void Node::print(int degree)
{
	std::cout << "|";
	for (int i = 0; i < degree; i++) {
		std::cout << "----";
	}

	std::cout << "Node " << this->childNodes.size() << " center:" << this->sphere.center << " r:" << this->sphere.radius << " " ;
    if(this->primitive != nullptr)
        std::cout << "   >>>    "  << this->primitive->body->GetName() << " p.center:" << *this->primitive->center;
    std::cout << " \n";


	for (Node* child : this->childNodes)
	{
		child->print(degree + 1);
	}
}

const Primitive& Node::getPrimitive() const {
    return *this->primitive;
}

BVH::BVH()
{
	root = new Node();
}

void BVH::broadPhaseCheck(Node* parent, CollisionData* cd) {
	for (int i = 0; i < parent->childNodes.size(); i++)
	{
		for (int j = 0; j < parent->childNodes.size(); j++)
		{
			if (j != i)
			{
				if ((parent->childNodes[i]->sphere.center - parent->childNodes[j]->sphere.center).Magnitude() < parent->childNodes[i]->sphere.radius + parent->childNodes[j]->sphere.radius)
				{
					//cd->CheckerCollision
					std::cout << "Potentielle collision a checker" << std::endl;
                    if(parent->childNodes[i]->primitive != nullptr){

                        Node* tempNode = parent->childNodes[j];
                        while(parent->childNodes[j]->primitive != nullptr && parent->childNodes[j]->childNodes.size() > 0){
                            tempNode = parent->childNodes[j]->childNodes[0];
                        }
                        if (parent->childNodes[i]->primitive->body->GetShapeType() == RigidBody::ShapeType::Sphere &&
                                tempNode->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan) {
                            CollisionDetector::sphereAndHalfSpace((const Sphere &) parent->childNodes[i]->getPrimitive(),
                                                                  (const Plane &) tempNode->getPrimitive(),
                                                                  cd);
                        } else if (parent->childNodes[i]->primitive->body->GetShapeType() == RigidBody::ShapeType::Sphere &&
                                tempNode->primitive->body->GetShapeType() == RigidBody::ShapeType::Cube) {
                            CollisionDetector::sphereAndHalfSpace((const Sphere &) tempNode->getPrimitive(),
                                                                  (const Plane &) parent->childNodes[i]->getPrimitive(),
                                                                  cd);
                        }

                    }

/*
                    if(parent->childNodes[i]->primitive != nullptr && parent->childNodes[j]->primitive != nullptr) {
                        std::cout << typeid(*parent->childNodes[i]->primitive).name() << " && " << typeid(*parent->childNodes[j]->primitive).name()<< std::endl;
                        std::cout << parent->childNodes[i]->primitive->body->GetShapeType() << " && " << parent->childNodes[j]->primitive->body->GetShapeType()<< std::endl;
                        std::cout << parent->childNodes[i]->primitive->body->GetName() << " && " << parent->childNodes[j]->primitive->body->GetName()<< std::endl;
                        if (parent->childNodes[i]->primitive->body->GetShapeType() == RigidBody::ShapeType::Sphere &&
                                parent->childNodes[j]->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan) {
                            CollisionDetector::sphereAndHalfSpace((const Sphere &) parent->childNodes[i]->getPrimitive(),
                                                               (const Plane &) parent->childNodes[j]->getPrimitive(),
                                                               cd);
                        } else if (parent->childNodes[i]->primitive->body->GetShapeType() == RigidBody::ShapeType::Sphere &&
                                   parent->childNodes[j]->primitive->body->GetShapeType() == RigidBody::ShapeType::Cube) {
                            CollisionDetector::sphereAndHalfSpace((const Sphere &) parent->childNodes[j]->getPrimitive(),
                                                               (const Plane &) parent->childNodes[i]->getPrimitive(),
                                                               cd);
                        }
                    }*/
				}
			}
		}

		if (!parent->childNodes[i]->isLeaf())
		{
			broadPhaseCheck(parent->childNodes[i], cd);
		}
	}
}

void BVH::broadPhaseCheck(CollisionData* cd)
{
	//CollisionData* cd = new CollisionData();
	broadPhaseCheck(this->root, cd);
}

void BVH::insertNode(Node* node)
{
	root->insertNode(node);
}

void BVH::print()
{
    std::cout << "==============" << std::endl;
    root->print(0);
    std::cout << "==============" << std::endl;
}
