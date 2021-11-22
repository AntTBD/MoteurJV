#include "RigidBody.h"


RigidBody::RigidBody() {

    this->invMass = 1.0f;

    this->linearDamping = 0.9f;
    this->position = Vector3();
    this->velocity = Vector3();
    this->acceleration = Vector3();

    this->m_angularDamping = 0.9f;
    this->orientation = Quaternion();
    this->angularVelocity = Vector3();
    this->angularAcceleration = Vector3();

    this->transformMatrix = Matrix34();

    this->m_forceAccum = Vector3();
    this->m_torqueAccum = Vector3();

    this->inertiaTensor = Matrix33();
    this->inverseInertiaTensor = Matrix33();
    this->inverseInertiaTensorWorld = Matrix33();


    this->dimensions = Vector3(1,1,1);
    this->shapeType = RigidBody::ShapeType::Sphere;

    this->name = nullptr;

    // init tenseur d'inertie
    this->SetInertiaTensorByType(this->shapeType);
    this->Integrate(0);
}

RigidBody::RigidBody(float mass, const Vector3 &position, const RigidBody::ShapeType &type, const Vector3 &dimensions):
        position(position), shapeType(type), dimensions(dimensions)
{
    this->SetMass(mass);

    this->linearDamping = 0.9f;
    this->velocity = Vector3();
    this->acceleration = Vector3();

    this->m_angularDamping = 0.9f;
    this->orientation = Quaternion();
    this->angularVelocity = Vector3();
    this->angularAcceleration = Vector3();

    this->transformMatrix = Matrix34();

    this->m_forceAccum = Vector3();
    this->m_torqueAccum = Vector3();

    this->inertiaTensor = Matrix33();
    this->inverseInertiaTensor = Matrix33();
    this->inverseInertiaTensorWorld = Matrix33();

    this->name = nullptr;

    // init tenseur d'inertie
    this->SetInertiaTensorByType(this->shapeType);
    this->Integrate(0);
}


RigidBody::RigidBody(float mass, const Vector3 &position, const Quaternion& orientation, const RigidBody::ShapeType &type, const Vector3 &dimensions):
        position(position), orientation(orientation), shapeType(type), dimensions(dimensions)
{
    this->SetMass(mass);

    this->linearDamping = 0.9f;
    this->velocity = Vector3();
    this->acceleration = Vector3();

    this->m_angularDamping = 0.9f;
    this->angularVelocity = Vector3();
    this->angularAcceleration = Vector3();

    this->transformMatrix = Matrix34();

    this->m_forceAccum = Vector3();
    this->m_torqueAccum = Vector3();

    this->inertiaTensor = Matrix33();
    this->inverseInertiaTensor = Matrix33();
    this->inverseInertiaTensorWorld = Matrix33();

    this->name = nullptr;

    // init tenseur d'inertie
    this->SetInertiaTensorByType(this->shapeType);
    this->Integrate(0);
}

RigidBody::RigidBody(float mass, const Vector3 &position, const Vector3 &velocity, const Quaternion &orientation, const Vector3 &angularVelocity, const RigidBody::ShapeType &type, const Vector3 &dimensions) :
        position(position), velocity(velocity), orientation(orientation), angularVelocity(angularVelocity), shapeType(type), dimensions(dimensions)
{
    this->SetMass(mass);

    this->linearDamping = 0.9f;
    this->acceleration = Vector3();

    this->m_angularDamping = 0.9f;
    this->angularAcceleration = Vector3();

    this->transformMatrix = Matrix34();

    this->m_forceAccum = Vector3();
    this->m_torqueAccum = Vector3();

    this->inertiaTensor = Matrix33();
    this->inverseInertiaTensor = Matrix33();
    this->inverseInertiaTensorWorld = Matrix33();

    this->name = nullptr;

    // init tenseur d'inertie
    this->SetInertiaTensorByType(this->shapeType);
    this->Integrate(0);
}

RigidBody::RigidBody(const RigidBody &rigidBody) {
    *this = rigidBody;

    // init tenseur d'inertie
    this->SetInertiaTensorByType(this->shapeType);
    this->Integrate(0);
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

Vector3 RigidBody::GetForceAccum() const {
    return this->m_forceAccum;
}

Vector3 RigidBody::GetTorqueAccum() const {
    return this->m_torqueAccum;
}

Vector3 RigidBody::GetDimensions() const {
    return this->dimensions;
}

RigidBody::ShapeType RigidBody::GetShapeType() const {
    return this->shapeType;
}

const char *RigidBody::GetName() const {
    return this->name;
}


void RigidBody::SetInvMass(float inverseMass) {
    this->invMass = inverseMass;
    this->SetInertiaTensorByType(this->shapeType);
    this->Integrate(0);
}

void RigidBody::SetMass(float mass) {
    // on s'assure de ne pas diviser par 0
    if(mass == 0) mass = 10e-5;
    assert(mass != 0 && "Mass = 0 and division by 0 is not possible");

    this->invMass = 1.f / mass;
    this->SetInertiaTensorByType(this->shapeType);
    this->Integrate(0);
}

void RigidBody::SetLinearDamping(float linearDamping) {
    this->linearDamping = linearDamping;
}

void RigidBody::SetPosition(const Vector3 &position) {
    this->position = position;
    this->Integrate(0);
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
    this->Integrate(0);
}

void RigidBody::SetAngularVelocity(const Vector3 &angularVelocity) {
    this->angularVelocity = angularVelocity;
}

void RigidBody::SetAngularAcceleration(const Vector3 &angularAcceleration) {
    this->angularAcceleration = angularAcceleration;
}

void RigidBody::SetTransform(const Matrix34 &transformMatrix) {
    this->transformMatrix = transformMatrix;
    this->Integrate(0);
}

void RigidBody::SetDimensions(const Vector3 &dimensions) {
    this->dimensions = dimensions;
    this->SetInertiaTensorByType(this->shapeType);
    this->Integrate(0);
}

void RigidBody::SetShapeType(RigidBody::ShapeType type) {
    this->shapeType = type;
    this->SetInertiaTensorByType(this->shapeType);
    this->Integrate(0);
}

void RigidBody::SetName(const char *name) {
    this->name = name;
}

void RigidBody::Integrate(float duration) {
    // 1. Calculer l�acc�l�ration lin�aire : a = 1/m * f
    // 2. Calculer l�acc�l�ration angulaire : aa = I(^-1)' * torq
    // 3. Mettre � jour la v�locit� lin�aire : v' = v * (damp)(^t)) + a * t;
    // 4. Mettre � jour la v�locit� angulaire : av' = av * (damp)(^t) + aa * t;
    // 5. Mettre � jour la position : p' = p + a * t
    // 6. Mettre � jour l�orientation : o = o + dt / 2 * w * o
    // 7. Calculer les valeurs d�riv�es (matrice de transformation et I(^-1)')
    // 8. Remettre � z�ro les accumulateurs (forces et couples).

    // 1. Calculer l�acc�l�ration lin�aire : a= 1/m * f
    this->UpdateAcceleration();

    // 2. Calculer l�acc�l�ration angulaire : av=I(^-1)' * torq;
    this->angularAcceleration = this->inverseInertiaTensorWorld * this->m_torqueAccum;

    // 3. Mettre � jour la v�locit� lin�aire : v' = v(damp)(^t)) + a * t;
    this->velocity *= pow(this->linearDamping, duration);
    this->velocity += this->acceleration * duration;

    // 4. Mettre � jour la v�locit� angulaire : av' = av * (damp)(^t) + aa * t;
    this->angularVelocity *= pow(this->m_angularDamping, duration);
    this->angularVelocity += this->angularAcceleration * duration;

    // 5. Mettre � jour la position : p' = p + a * t
    this->position += this->velocity * duration;

    // 6. Mettre � jour l�orientation : o = o + dt / 2 * w * o
    // w = [0, av.x, av.y, av.z]
    //Quaternion w(this->angularVelocity.GetX(), this->angularVelocity.GetY(), this->angularVelocity.GetZ(), 0);
    //this->orientation += (duration / 2.f) * this->orientation.RotatedByVector(this->angularVelocity);
    this->orientation.UpdateByAngularVelocity(this->angularVelocity, duration);

    // 7. Calculer les valeurs d�riv�es (matrice de transformation et I(^-1)')
    this->CalculateDerivedData();

    // 8. Remettre � z�ro les accumulateurs (forces et couples).
    this->ClearAccumulator();
}

void RigidBody::UpdateAcceleration()
{
    // Update acceleration with sumForces, invMass
    this->acceleration = this->m_forceAccum;
}

void RigidBody::CalculateDerivedData() {
    this->orientation.Normalize();

    // Matrice de transformation
    // Calculate the transform matrix for the body.
    this->transformMatrix.SetOrientationAndPosition(this->orientation, this->position);


    // I(^-1)'
    // Calculate the inertiaTensor in world space.
    this->inverseInertiaTensorWorld = this->inverseInertiaTensor.Transform(this->transformMatrix);
}

void RigidBody::SetInertiaTensorByType(ShapeType type) {
    this->shapeType = type;

    switch (this->shapeType) {
        case 0: // sphere
            //  I = [ 1/5 * m * (r.y� + r.z�),            0            ,           0             ,
            //                  0             , 1/5 * m * (r.x� + r.z�),           0             ,
            //                  0             ,            0            , 1/5 * m * (r.x� + r.y�) ]
            //  where m is the mass and r.x, r.y and r.z are radii along respective axes.
            // You can see by inspection that this reduces to the sphere inertia tensor when the radii are all equal
            this->inertiaTensor = Matrix33({
               1.f / 5.f * this->GetMass() * (pow(this->dimensions.GetY(), 2.f) + pow(this->dimensions.GetZ(), 2.f)), 0.f, 0.f,
               0.f, 1.f / 5.f * this->GetMass() * (pow(this->dimensions.GetX(), 2.f) + pow(this->dimensions.GetZ(), 2.f)), 0.f,
               0.f, 0.f, 1.f / 5.f * this->GetMass() * (pow(this->dimensions.GetX(), 2.f) + pow(this->dimensions.GetY(), 2.f))
            });
            break;
        case 1: // cube
        case 3: // plan
            //  I = [ 1/12 * m * (d.y� + d.z�),            0            ,           0             ,
            //                  0             , 1/12 * m * (d.x� + d.z�),           0             ,
            //                  0             ,            0            , 1/12 * m * (d.x� + d.y�) ]
            //  where m is the mass and d.x, d.y and d.z are the extent of the cuboid along each axis.
            this->inertiaTensor = Matrix33({
                1.f / 12.f * this->GetMass() * (pow(this->dimensions.GetY(), 2.f) + pow(this->dimensions.GetZ(), 2.f)), 0.f, 0.f,
                0.f, 1.f / 12.f * this->GetMass() * (pow(this->dimensions.GetX(), 2.f) + pow(this->dimensions.GetZ(), 2.f)), 0.f,
                0.f, 0.f, 1.f / 12.f * this->GetMass() * (pow(this->dimensions.GetX(), 2.f) + pow(this->dimensions.GetY(), 2.f))
            });
            break;
        case 2: // cylindre
            // d.x = r.o
            // d.y = h / 2
            // d.z = r.i
            //  I = [ 1/12 * m * h� + 1/4 * m * (r.o� + r.i�),            0            ,           0             ,
            //                  0             , 1/12 * m * h� + 1/4 * m * (r.o� + r.i�),           0             ,
            //                  0             ,            0            , 1/12 * m * h� + 1/4 * m * (r.o� + r.i�) ]
            //  where m is the mass and d.x, d.y and d.z are the extent of the cuboid along each axis.
            this->inertiaTensor = Matrix33({
               1.f / 12.f * this->GetMass() * pow(this->dimensions.GetY(), 2.f) + 1.f/4.f * this->GetMass() * (pow(this->dimensions.GetX(), 2.f) + pow(this->dimensions.GetZ(), 2.f)), 0.f, 0.f,
               0.f, 1.f / 12.f * this->GetMass() * pow(this->dimensions.GetY(), 2.f) + 1.f/4.f * this->GetMass() * (pow(this->dimensions.GetX(), 2.f) + pow(this->dimensions.GetZ(), 2.f)), 0.f,
               0.f, 0.f, 1.f / 12.f * this->GetMass() * pow(this->dimensions.GetY(), 2.f) + 1.f/4.f * this->GetMass() * (pow(this->dimensions.GetX(), 2.f) + pow(this->dimensions.GetZ(), 2.f))
            });
            break;
    }

    this->inverseInertiaTensor = this->inertiaTensor.Inverse();
    this->inverseInertiaTensorWorld = this->inverseInertiaTensor.Transform(this->transformMatrix);
}

void RigidBody::AddForce(const Vector3 &force) {
    this->m_forceAccum += force;
}

void RigidBody::AddTorque(const Vector3& torque)
{
    this->m_torqueAccum += torque;
}

void RigidBody::AddForceAtPoint(const Vector3 &force, const Vector3 &worldPoint) {
    // Convert to coordinates relative to center of mass.
    Vector3 pt = worldPoint - this->position;
    this->m_forceAccum += force;
    this->m_torqueAccum += pt.CrossProduct(force);
}

void RigidBody::AddForceAtBodyPoint(const Vector3 &force, const Vector3 &localPoint) {
    // Convert to coordinates relative to center of mass.
    Vector3 pt = this->GetPointInWorldSpace(localPoint);
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

std::string RigidBody::toString() const {
    std::stringstream stream;
    stream << *this;
    return stream.str();
}

std::ostream &operator<<(std::ostream &os, const RigidBody &rigidBody) {
    os << "Mass : " << rigidBody.GetMass() << ", Acceleration : " << rigidBody.GetAcceleration() << ", Velocity : " << rigidBody.GetVelocity() << ", Position : " << rigidBody.GetPosition() << ", SumForces : " << rigidBody.GetForceAccum();

    if(rigidBody.GetName() != nullptr){
        os << ", Name : " << rigidBody.GetName();
    }
    return os;
}
