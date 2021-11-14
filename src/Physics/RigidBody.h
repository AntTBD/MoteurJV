#pragma once

#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "../Math/Matrix34.h"

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

	// same as linear damping
	// but for rotation
	float m_angularDamping;

	// Accumulated force
	// added by ForceGenerator
	Vector3 m_forceAccum;

	// Accumulated torque
	// added by ForceGenerator
	Vector3 m_torqueAccum;

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

	// Add force on the Center of mass (no torque generated)
	void AddForce(const Vector3& force);

	// Add force at a point in world coordinate.
	// Generate force and torque
	void AddForceAtPoint(const Vector3& force, const Vector3& worldPoint);

	// Add force at a point in local coordinate.
	// the point is converted in world coordinated by using the transform matrix.
	// Generate force and torque
	void AddForceAtBodyPoint(const Vector3& force, const Vector3& localPoint);

	// called each frame to reset m_forceAccum and m_torqueAccum
	void ClearAccumulator();

private:
	// call each frame to calculate the transformMatrix and normalize the orientation
	void CalculateDerivedData();

};

