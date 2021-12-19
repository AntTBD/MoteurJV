#pragma once

#include <vector>
#include <stdio.h>
#include <algorithm>
#include <iostream>

#include "BoundingSphere.h"
#include "../Physic/Collisions/Primitive.h"
#include "../Physic/Collisions/CollisionData.h"

class Primitive;
class CollisionData;

class Node {
private:

public:
    Node* parentNode;
	BoundingSphere sphere;
	Primitive* primitive;
	std::vector<Node*> childNodes;

	//Constructor
	Node();
	Node(Primitive* _primitive);

	//Sphere
	float getSphereVolume();
	BoundingSphere sphereBouding2Nodes(BoundingSphere sphereA, BoundingSphere sphereB);

	//Node
	bool hasParent() { return parentNode != nullptr; }
	bool isLeaf() { return childNodes.size() == 0; }
	Node* getBrotherNode();
	void RemoveFromChild(Node* node);

	void insertNode(Node* node);
	void deleteNode();

	void print(int degree);

};

class BVH
{
private:

public:
    Node* root;
	//Constructor
	BVH();

	void broadPhaseCheck(Node* parent, CollisionData* cd);
	void broadPhaseCheck();
	void insertNode(Node* node);
};