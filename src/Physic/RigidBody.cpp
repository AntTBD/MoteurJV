#include "RigidBody.h"


RigidBody::RigidBody() {
    this->SetInertiaTensorByType(RigidBody::FormType::Sphere);
}

RigidBody::~RigidBody() {

}

float RigidBody::GetInvMass() const {
    return this->invMass;
}

float RigidBody::GetMass() const {
    return 1.f / this->invMass;
}

float RigidBody::GetLinearDamping() const {
    return this->linearDamping;
}

Vector3 RigidBody::GetPosition() const {
    return this->position;
}

Vector3 RigidBody::GetVelocity() const {
    return this->velocity;
}

Vector3 RigidBody::GetAcceleration() const {
    return this->acceleration;
}

float RigidBody::GetAngularDamping() const {
    return this->m_angularDamping;
}

Quaternion RigidBody::GetOrientation() const {
    return this->orientation;
}

Vector3 RigidBody::GetAngularVelocity() const {
    return this->angularVelocity;
}

Vector3 RigidBody::GetAngularAcceleration() const {
    return this->angularAcceleration;
}

Matrix34 RigidBody::GetTransform() const {
    return this->transformMatrix;
}

Vector3 RigidBody::GetDimensions() const {
    return this->dimensions;
}

void RigidBody::SetInvMass(float inverseMass) {
    this->invMass = inverseMass;
}

void RigidBody::SetMass(float mass) {
    // on s'assure de ne pas diviser par 0
    if(mass == 0) mass = 10e-10;
    assert(mass != 0 && "Mass = 0 and division by 0 is not possible");

    this->invMass = 1.f / mass;
}

void RigidBody::SetLinearDamping(float linearDamping) {
    this->linearDamping = linearDamping;
}

void RigidBody::SetPosition(const Vector3 &position) {
    this->position = position;
}

void RigidBody::SetVelocity(const Vector3 &velocity) {
    this->velocity = velocity;
}

void RigidBody::SetAcceleration(const Vector3 &acceleration) {
    this->acceleration = acceleration;
}

void RigidBody::SetAngularDamping(float angularDamping) {
    this->m_angularDamping = angularDamping;
}

void RigidBody::SetOrientation(const Quaternion &orientation) {
    this->orientation = orientation;
}

void RigidBody::SetAngularVelocity(const Vector3 &rotation) {
    this->angularVelocity = rotation;
}

void RigidBody::SetAngularAcceleration(const Vector3 &angularAcceleration) {
    this->angularAcceleration = angularAcceleration;
}

void RigidBody::SetTransform(const Matrix34 &transformMatrix) {
    this->transformMatrix = transformMatrix;
}

void RigidBody::SetDimensions(const Vector3 &dimensions) {
    this->dimensions = dimensions;
}

void RigidBody::Integrate(float duration) {
    // 1. Calculer l’accélération linéaire : a = 1/m * f
    // 2. Calculer l’accélération angulaire : aa = I(^-1)' * torq
    // 3. Mettre à jour la vélocité linéaire : v' = v * (damp)(^t)) + a * t;
    // 4. Mettre à jour la vélocité angulaire : av' = av * (damp)(^t) + aa * t;
    // 5. Mettre à jour la position : p' = p + a * t
    // 6. Mettre à jour l’orientation : o = o + dt / 2 * w * o
    // 7. Calculer les valeurs dérivées (matrice de transformation et I(^-1)')
    // 8. Remettre à zéro les accumulateurs (forces et couples).

    // 1. Calculer l’accélération linéaire : a= 1/m * f
    this->UpdateAcceleration();

    // 2. Calculer l’accélération angulaire : av=I(^-1)' * torq;
    this->angularAcceleration = this->inverseInertiaTensorWorld * this->m_torqueAccum;

    // 3. Mettre à jour la vélocité linéaire : v' = v(damp)(^t)) + a * t;
    this->velocity *= pow(this->linearDamping, duration);
    this->velocity += this->acceleration * duration;

    // 4. Mettre à jour la vélocité angulaire : av' = av * (damp)(^t) + aa * t;
    this->angularVelocity *= pow(this->m_angularDamping, duration);
    this->angularVelocity += this->angularAcceleration * duration;

    // 5. Mettre à jour la position : p' = p + a * t
    this->position += this->velocity * duration;

    // 6. Mettre à jour l’orientation : o = o + dt / 2 * w * o
    // w = [0, av.x, av.y, av.z]
    Quaternion w(0, this->angularVelocity.GetX(), this->angularVelocity.GetY(), this->angularVelocity.GetZ());
    this->orientation += (duration / 2.f) * w * this->orientation;

    // 7. Calculer les valeurs dérivées (matrice de transformation et I(^-1)')
    // Normalize the orientation, and update the matrices with the new
    // position and orientation.
    this->CalculateDerivedData();

    // 8. Remettre à zéro les accumulateurs (forces et couples).
    this->ClearAccumulator();
}

void RigidBody::UpdateAcceleration()
{
    // Update acceleration with sumForces, invMass
    this->acceleration = this->m_forceAccum;
}

void RigidBody::CalculateDerivedData() {
    this->orientation.Normalized();

    // Matrice de transformation
    // Calculate the transform matrix for the body.
    this->transformMatrix.SetOrientationAndPosition(this->orientation, this->position);


    // I(^-1)'
    // Calculate the inertiaTensor in world space.
    this->inverseInertiaTensorWorld = this->inverseInertiaTensor.Transform(this->transformMatrix);
}

void RigidBody::SetInertiaTensorByType(FormType type) {
    this->formType = type;
    switch (this->formType) {
        case 0: // sphere
            //  I = [ 1/5 * m * (r.y² + r.z²),            0            ,           0             ,
            //                  0             , 1/5 * m * (r.x² + r.z²),           0             ,
            //                  0             ,            0            , 1/5 * m * (r.x² + r.y²) ]
            //  where m is the mass and r.x, r.y and r.z are radii along respective axes.
            // You can see by inspection that this reduces to the sphere inertia tensor when the radii are all equal
            this->inertiaTensor = Matrix33({
               1.f / 5.f * this->GetMass() * (pow(this->dimensions.GetY(), 2.f) + pow(this->dimensions.GetZ(), 2.f)), 0.f, 0.f,
               0.f, 1.f / 5.f * this->GetMass() * (pow(this->dimensions.GetX(), 2.f) + pow(this->dimensions.GetZ(), 2.f)), 0.f,
               0.f, 0.f, 1.f / 5.f * this->GetMass() * (pow(this->dimensions.GetX(), 2.f) + pow(this->dimensions.GetY(), 2.f))
            });
            this->inverseInertiaTensor = this->inertiaTensor.Inverse();
            break;
        case 1: // cube
            //  I = [ 1/12 * m * (d.y² + d.z²),            0            ,           0             ,
            //                  0             , 1/12 * m * (d.x² + d.z²),           0             ,
            //                  0             ,            0            , 1/12 * m * (d.x² + d.y²) ]
            //  where m is the mass and d.x, d.y and d.z are the extent of the cuboid along each axis.
            this->inertiaTensor = Matrix33({
                1.f / 12.f * this->GetMass() * (pow(this->dimensions.GetY(), 2.f) + pow(this->dimensions.GetZ(), 2.f)), 0.f, 0.f,
                0.f, 1.f / 12.f * this->GetMass() * (pow(this->dimensions.GetX(), 2.f) + pow(this->dimensions.GetZ(), 2.f)), 0.f,
                0.f, 0.f, 1.f / 12.f * this->GetMass() * (pow(this->dimensions.GetX(), 2.f) + pow(this->dimensions.GetY(), 2.f))
            });
            this->inverseInertiaTensor = this->inertiaTensor.Inverse();
            break;
        case 2: // cylindre
            // d.x = r.o
            // d.y = h
            // d.z = r.i
            //  I = [ 1/12 * m * h² + 1/4 * m * (r.o² + r.i²),            0            ,           0             ,
            //                  0             , 1/12 * m * h² + 1/4 * m * (r.o² + r.i²),           0             ,
            //                  0             ,            0            , 1/12 * m * h² + 1/4 * m * (r.o² + r.i²) ]
            //  where m is the mass and d.x, d.y and d.z are the extent of the cuboid along each axis.
            this->inertiaTensor = Matrix33({
               1.f / 12.f * this->GetMass() * pow(this->dimensions.GetZ(), 2.f) + 1.f/4.f * this->GetMass() * (pow(this->dimensions.GetX(), 2.f) + pow(this->dimensions.GetZ(), 2.f)), 0.f, 0.f,
               0.f, 1.f / 12.f * this->GetMass() * pow(this->dimensions.GetZ(), 2.f) + 1.f/4.f * this->GetMass() * (pow(this->dimensions.GetX(), 2.f) + pow(this->dimensions.GetZ(), 2.f)), 0.f,
               0.f, 0.f, 1.f / 12.f * this->GetMass() * pow(this->dimensions.GetZ(), 2.f) + 1.f/4.f * this->GetMass() * (pow(this->dimensions.GetX(), 2.f) + pow(this->dimensions.GetZ(), 2.f))
            });
            this->inverseInertiaTensor = this->inertiaTensor.Inverse();
            break;
    }
}

void RigidBody::AddForce(const Vector3 &force) {
    this->m_forceAccum += force;
}

void RigidBody::AddForceAtPoint(const Vector3 &force, const Vector3 &worldPoint) {
    // Convert to coordinates relative to center of mass.
    Vector3 pt = this->position;
    pt -= position;
    this->m_forceAccum += force;
    this->m_torqueAccum += pt.CrossProduct(force);
}

void RigidBody::AddForceAtBodyPoint(const Vector3 &force, const Vector3 &localPoint) {
    // Convert to coordinates relative to center of mass.
    Vector3 pt = this->GetPointInWorldSpace(this->position);
    this->AddForceAtPoint(force, pt);
}

void RigidBody::ClearAccumulator() {
    this->m_forceAccum.SetZero();
    this->m_torqueAccum.SetZero();
}


Vector3 RigidBody::GetPointInLocalSpace(const Vector3 &point) const
{
    return this->transformMatrix.TransformInversePosition(point);
}

Vector3 RigidBody::GetPointInWorldSpace(const Vector3 &point) const
{
    return this->transformMatrix.TransformPosition(point);
}



Vector3 RigidBody::GetDirectionInLocalSpace(const Vector3 &direction) const
{
    return this->transformMatrix.TransformInverseDirection(direction);
}

Vector3 RigidBody::GetDirectionInWorldSpace(const Vector3 &direction) const
{
    return this->transformMatrix.TransformDirection(direction);
}
