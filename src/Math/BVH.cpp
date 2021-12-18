#include "BVH.h"

Node::Node()
{
	this->parentNode = nullptr;
	this->sphere = BoundingSphere();
	this->sphere.center = Vector3();
	this->sphere.radius = 0;
}

Node::Node(BoundingSphere sphere)
{
	this->parentNode = nullptr;
	this->sphere = sphere;
}

Node::Node(Primitive _primitive)
{
	this->parentNode = nullptr;
	this->primitive = _primitive;
}

Node::Node(BoundingSphere sphere, Primitive _primitive)
{
	this->parentNode = nullptr;
	this->sphere = sphere;
	this->primitive = _primitive;
}

float Node::getSphereVolume()
{
	return  (4 / 3) * 3.14 * sphere.radius * sphere.radius;
}

BoundingSphere Node::sphereBouding2Nodes(BoundingSphere sphereA, BoundingSphere sphereB)
{
	BoundingSphere newSphere;

	float distanceAB = (sphereA.center + sphereB.center).Magnitude();

	newSphere.center = Vector3(
		(sphereA.center.GetX() + sphereB.center.GetX()) / 2,
		(sphereA.center.GetY() + sphereB.center.GetY()) / 2,
		(sphereA.center.GetZ() + sphereB.center.GetZ()) / 2);

	newSphere.radius = distanceAB + sphereA.radius + sphereB.radius;

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
	if (isLeaf())
	{
		this->parentNode->RemoveFromChild(this);

		Node* newParent;
		this->parentNode->childNodes.push_back(newParent);
		this->parentNode = newParent;
		newParent->childNodes.push_back(node);
		newParent->childNodes.push_back(this);
	}
	else
	{
		float minSearch = std::numeric_limits<float>::max();
		Node* childToSave = nullptr;

		for (Node* child : this->childNodes)
		{
			BoundingSphere sphere = this->sphereBouding2Nodes(child->sphere, node->sphere);

			if (sphere.radius < minSearch)
			{
				minSearch = sphere.radius;
				childToSave = child;
			}
		}

		childToSave->insertNode(node);
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

	std::cout << "Node \n";

	for (Node* child : this->childNodes)
	{
		child->print(degree + 1);
	}
}

BVH::BVH()
{
	root = new Node();
}

BVH::BVH(BoundingSphere sphere)
{
	root = new Node(sphere);
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
					std::cout << "Potentielle collision à checker" << std::endl;
				}
			}
		}

		if (!parent->childNodes[i]->isLeaf())
		{
			broadPhaseCheck(parent->childNodes[i], cd);
		}
	}
}

void BVH::broadPhaseCheck()
{
	CollisionData* cd = new CollisionData();
	broadPhaseCheck(this->root, cd);
}

void BVH::insertNode(Node* node)
{
	root->insertNode(node);
}