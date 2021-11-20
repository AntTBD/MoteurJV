#pragma once

#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "../Math/Matrix33.h"
#include "../Math/Matrix34.h"
#include <vector>
#include <math.h>

class RigidBody
{
public:
    // 0 = Sphere
    // 1 = Cube
    // 2 = Cylindre
    enum ShapeType{
        Sphere,
        Cube,
        Cylindre,
        _enumEnd // used to loop on this enum
    };
private:
    // ------------- Mass -------------
	// same as for Particle
	float invMass;

    // ------------- Position -------------
    // same as for Particle
	float linearDamping;
	Vector3 position;
	Vector3 velocity;
    Vector3 acceleration;

    // ------------- Rotation -------------
    // same as linear damping
    // but for rotation
    float m_angularDamping;

	// Quaternion of the rigid body
	Quaternion orientation;

	// Angular velocity of the rigid body
    // <=> rotation
	Vector3 angularVelocity;

    // Angular acceleration of the rigid body
    Vector3 angularAcceleration;

    // ------------- Transform -------------
	// Calculates transform matrix from orientation and  rotation
	Matrix34 transformMatrix;


    // ------------- Force -------------
	// Accumulated force
	// added by ForceGenerator
	Vector3 m_forceAccum;

	// Accumulated torque
	// added by ForceGenerator
	Vector3 m_torqueAccum;

    // ------------- Tenseurs d'inertie -------------
    // Sph�re de densit� constante
    Matrix33 inertiaTensor;
    Matrix33 inverseInertiaTensor;
    Matrix33 inverseInertiaTensorWorld;

    // ------------- Dimensions ---------------------
    Vector3 dimensions;
    ShapeType shapeType;

public:
	RigidBody();
    RigidBody(float mass, const Vector3 &position, const RigidBody::ShapeType &type = RigidBody::ShapeType::Sphere, const Vector3 &dimensions = Vector3(1, 1, 1));
    RigidBody(float mass, const Vector3 &position, const Quaternion& orientation, const RigidBody::ShapeType &type = RigidBody::ShapeType::Sphere, const Vector3 &dimensions = Vector3(1, 1, 1));
	RigidBody(float mass, const Vector3& position, const Vector3& velocity, const Quaternion& orientation, const Vector3& angularVelocity, const RigidBody::ShapeType &type = RigidBody::ShapeType::Sphere, const Vector3 &dimensions = Vector3(1, 1, 1));
	RigidBody(const RigidBody& rigidBody);
	~RigidBody();

    // ------------- Mass -------------
	float GetInvMass() const;
    float GetMass() const;
    // ------------- Position -------------
	float GetLinearDamping() const;
	Vector3 GetPosition() const;
	Vector3 GetVelocity() const;
    Vector3 GetAcceleration() const;
    // ------------- Rotation -------------
    float GetAngularDamping() const;
	Quaternion GetOrientation() const;
	Vector3 GetAngularVelocity() const;
    Vector3 GetAngularAcceleration() const;
    // ------------- Transform -------------
    Matrix34 GetTransform() const;
    // ------------- Force -------------
    Vector3 GetForceAccum() const;
    Vector3 GetTorqueAccum() const;
    // ------------- Dimensions ---------------------
    Vector3 GetDimensions() const;
    RigidBody::ShapeType GetShapeType() const;

    // ------------- Mass -------------
	void SetInvMass(float inverseMass);
    void SetMass(float mass);
    // ------------- Position -------------
	void SetLinearDamping(float linearDamping);
	void SetPosition(const Vector3& position);
	void SetVelocity(const Vector3& velocity);
    void SetAcceleration(const Vector3& acceleration);
    // ------------- Rotation -------------
    void SetAngularDamping(float angularDamping);
	void SetOrientation(const Quaternion& orientation);
	void SetAngularVelocity(const Vector3& angularVelocity);
    void SetAngularAcceleration(const Vector3& angularAcceleration);
    // ------------- Transform -------------
	void SetTransform(const Matrix34& transformMatrix);
    // ------------- Dimensions ---------------------
    void SetDimensions(const Vector3& dimensions);
    void SetShapeType(RigidBody::ShapeType type);



    // ------------- Update -------------
	// Integrate the rigid body by modifying position, orientation and velocities
	void Integrate(float duration);

    // Update acceleration based on sumForces
    void UpdateAcceleration();

    // ------------- Force -------------
    // Add force on the Center of mass (no torque generated)
    void AddForce(const Vector3& force);
    void AddTorque(const Vector3& torque);

	// Add force at a point in world coordinate.
	// Generate force and torque
	void AddForceAtPoint(const Vector3& force, const Vector3& worldPoint);

	// Add force at a point in local coordinate.
	// the point is converted in world coordinated by using the transform matrix.
	// Generate force and torque
	void AddForceAtBodyPoint(const Vector3& force, const Vector3& localPoint);

	// called each frame to reset m_forceAccum and m_torqueAccum
	void ClearAccumulator();


    // ------------- Local <=> World -------------
    Vector3 GetPointInLocalSpace(const Vector3 &point) const;
    Vector3 GetPointInWorldSpace(const Vector3 &point) const;

    Vector3 GetDirectionInLocalSpace(const Vector3 &direction) const;
    Vector3 GetDirectionInWorldSpace(const Vector3 &direction) const;

    std::string toString() const;

    // << operator
    friend std::ostream& operator<< (std::ostream& os, const RigidBody& rigidBody);

private:
	// call each frame to calculate the transformMatrix and normalize the orientation
	void CalculateDerivedData();

    // Get tenseur d'inertie en fonction du type du rigidbody
    // 0 = Sphere de densit� constante (default)
    // 1 = Cube de densit� constante
    // 2 = Cylindre de densit� constante
    void SetInertiaTensorByType(ShapeType type = ShapeType::Sphere);


};

