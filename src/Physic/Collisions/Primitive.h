#pragma once
#include "../RigidBody.h"


class Primitive
{
public:
	RigidBody* body;	// Primitive d'un objet
	Matrix34 offset;	// Transformation par rapport au centre de l'objet
	Vector3 center;


    // Getters & Setters
    Vector3 getCenter();
    void setCenter(Vector3 center);
	

	virtual float distancePoint(Vector3 point);

};