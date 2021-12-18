#pragma once

#include <vector>
#include <stdio.h>
#include <algorithm>
#include <iostream>

#include "BoundingSphere.h"
#include "Physic/Collisions/Primitive.h"
#include "Physic/Collisions/CollisionData.h"

class Primitive;
class CollisionData;

class Node {
private:
	Node* parentNode;
	std::vector<Node*> childNodes;
	
	BoundingSphere sphere;
	Primitive primitive;

public:
	//Constructor
	Node();
	Node(BoundingSphere sphere);
	Node(Primitive prim);

	//Sphere
	float getSphereVolume();
	BoundingSphere addSphere(BoundingSphere sphereA, BoundingSphere sphereB);

	//Node
	bool hasParent() { return parentNode != nullptr; }
	bool isLeaf() { return childNodes.size() == 0; }
	Node* getBrother();
	void RemoveFromChild(Node* node);

	void insertNode(Node* node);
	void deleteNode();

	void print(int degree);

};