#include "CollisionDetector.h"

unsigned CollisionDetector::sphereAndHalfSpace(
        const Sphere &sphere,
        const Plane &plane,
        CollisionData *data) {
    return 0;
}

unsigned CollisionDetector::sphereAndTruePlane(
        const Sphere &sphere,
        const Plane &plane,
        CollisionData *data) {
    return 0;
}

unsigned CollisionDetector::sphereAndSphere(
        const Sphere &sphere1,
        const Sphere &sphere2,
        CollisionData *data) {
    return 0;
}

unsigned CollisionDetector::boxAndHalfSpace(
        const Box &box,
        const Plane &plane,
        CollisionData *data) {
    return 0;
}

unsigned CollisionDetector::boxAndBox(
        const Box &box1,
        const Box &box2,
        CollisionData *data) {
    return 0;
}

unsigned CollisionDetector::boxAndPoint(
        const Box &box,
        const Vector3 &point,
        CollisionData *data) {
    return 0;
}

unsigned CollisionDetector::boxAndSphere(
        const Box &box,
        const Sphere &sphere,
        CollisionData *data) {
    return 0;
}
