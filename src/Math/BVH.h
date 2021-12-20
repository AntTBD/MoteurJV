#pragma once

#include <vector>
#include <stdio.h>
#include <algorithm>
#include <iostream>

#include "BoundingSphere.h"
#include "../Physic/Collisions/Primitive.h"
#include "../Physic/Collisions/CollisionData.h"
#include "../Physic/Collisions/CollisionDetector.h"

#include "../3DScene/OpenGLRendererManager.h"
#include "../EngineManager.h"

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

    const Primitive& getPrimitive() const;

};

class BVH
{
private:

public:
    Node* root;
	//Constructor
	BVH();

	void broadPhaseCheck(Node* parent, CollisionData* cd);
    void broadPhaseCheckChildPrimitive(Node *child1, Node *child2, CollisionData* cd);
	void broadPhaseCheck(CollisionData* cd);
	void insertNode(Node* node);

    void print();
};