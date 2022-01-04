#pragma once

#include "Box.h"
#include "Plane.h"
#include "Sphere.h"

#include "CollisionData.h"

class CollisionDetector {
public:

    static unsigned sphereAndHalfSpace(
            const Sphere &sphere,
            const Plane &plane,
            CollisionData *data
    );

    static unsigned sphereAndSphere(
            const Sphere &sphere1,
            const Sphere &sphere2,
            CollisionData *data
    );

    static unsigned boxAndHalfSpace(
            const Box &box,
            const Plane &plane,
            CollisionData *data
    );

    static unsigned boxAndSphere(
            const Box &box,
            const Sphere &sphere,
            CollisionData *data
    );
};


