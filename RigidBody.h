#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix34.h"

class RigidBody
{
private:
	// same as for Particle
	float inverseMasse;
	float linearDamping;
	Vector3 position;
	Vector3 velocity;

	// Quaternion of the rigid body
	Quaternion orientation;

	// Angular velocity of the rigid body
	Vector3 rotation;

	// Calculates transform matrix from orientation and  rotation
	Matrix34 transformMatrix;

public:
	RigidBody();
	RigidBody(float inverseMasse, float linearDamping, const Vector3& position, const Vector3& velocity);
	RigidBody(float inverseMasse, float linearDamping, const Vector3& position, const Vector3& velocity, const Quaternion& orientation, const Vector3& rotation, const Matrix34& transformMatrix);
	RigidBody(const RigidBody& rigidBody);
	~RigidBody();

	float GetInverseMasse() const;
	float GetLinearDamping() const;
	Vector3 GetPosition() const;
	Vector3 GetVelocity() const;
	Quaternion GetOrientation() const;
	Vector3 GetRotation() const;
	Matrix34 GetTransformMatrix() const;

	void SetInverseMasse(float inverseMasse);
	void SetLinearDamping(float linearDamping);
	void SetPosition(const Vector3& position);
	void SetVelocity(const Vector3& velocity);
	void SetOrientation(const Quaternion& orientation);
	void SetRotation(const Vector3& rotation);
	void SetTransformMatrix(const Matrix34& transformMatrix);


	// Integrate the rigid body by modifying position, orientation and velocities
	void Integrate(float duration);

private:
	// call each frame to calculate the transformMatrix and normalize the orientation
	void CalculateDerivedData();

};

