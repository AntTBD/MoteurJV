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

float Node::getSphereVolume()
{
	return  (4 / 3) * 3.14 * sphere.radius * sphere.radius;
}

BoundingSphere Node::addSphere(BoundingSphere sphereA, BoundingSphere sphereB)
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

Node* Node::getBrother()
{
	Node* brother = nullptr;
	if (hasParent())
	{

	}
}