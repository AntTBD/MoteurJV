#include "CollisionDetector.h"

unsigned CollisionDetector::sphereAndHalfSpace(
        const Sphere &sphere,
        const Plane &plane,
        CollisionData *data) {

    // Make sure we have contacts
    //if (data->contactsLeft  <= 0) return 0;

    // Sphere position
    Vector3 position = sphere.getCenter();

    // Find the distance from the plane
   // float sphereDistance = plane.getNormal().DotProduct(position) - sphere.radius - plane.getOffset();
    //if (sphereDistance >= 0) return 0;

    // Create the contact ; it has normal in the plane direction
    //...


    //...


    return 1;
}

unsigned CollisionDetector::sphereAndTruePlane(
        const Sphere &sphere,
        const Plane &plane,
        CollisionData *data) {

    // Make sure we have contacts
    // if(data->contactsLeft<=0) return 0;
    // Sphere position
    Vector3 position = sphere.getCenter();
    // Find the distance from the plane
    //float centerDistance = plane.getNormal().DotProduct(position) - plane.getOffset();

    // Check radius
    //if (centerDistance * centerDistance > sphere.radius * sphere.radius)
    //{
    //    return 0;
    //}

    // Check plane side
   // Vector3 normal = plane.getNormal();
    //float penetration = -centerDistance;
    //if (centerDistance < 0)
    //{
    //    normal *= -1;
    //    penetration = -penetration;
    //}
    //penetration += sphere.radius;


    // Create the contact
    //...

    //...
    return 1;
}

unsigned CollisionDetector::sphereAndSphere(
    const Sphere& sphere1,
    const Sphere& sphere2,
    CollisionData* data) {

    // Make sure we have contacts
    //if(data->contactsLeft <= 0) return 0;

    // Sphere positions
    Vector3 positionOne = sphere1.getCenter();
    Vector3 positionTwo = sphere2.getCenter();

    // Find the vector between the objects
    Vector3 midline = positionOne - positionTwo;
    float size = midline.Magnitude();

    // See if it is large enough
    if (size <= 0.0f || size >= sphere1.radius + sphere2.radius) 
    {
        return 0;
    }

    // Creating the normal
    Vector3 normal = midline * (1.0f/size);
    // contacts.....




    return 1;
}

unsigned CollisionDetector::boxAndHalfSpace(
        const Box &box,
        const Plane &plane,
        CollisionData *data) {
    // Make sure we have contacts
    //if (data->contactsLeft <= 0) return 0;
    // check for intersection
    /*if (!IntersectionTests::boxAndHalfSpace(box, plane))
    {
        return 0;
    }
    */

    //
    static float mults[8][3] = { {1,1,1},{-1,1,1},{1,-1,1},{-1,-1,1}, {1,1,-1},{-1,1,-1},{1,-1,-1},{-1,-1,-1} };
    //...




    //...






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
    Vector3 center = sphere.getCenter();
    //Vector3 relCenter = box.transform.transformInverse(center);
    // Early out check to see if we can exclude the contact. 
    //if (relCenter.GetX() - sphere.radius > box.halfSize.GetX() ||
    //    relCenter.GetY() - sphere.radius > box.halfSize.GetY() ||
     //   relCenter.GetZ() - sphere.radius > box.halfSize.GetZ())
    //{
    //    return 0;
    //}
    Vector3 closestPt(0, 0, 0);
    float dist;

    //Clamp each coordinate to the box
    //dist = relCenter.GetX();
    //if (dist > box.halfSize.GetX()) dist = box.halfSize.GetX();
    //if (dist > -box.halfSize.GetX()) dist = -box.halfSize.GetX();
    //closestPt.SetX(dist);

    //dist = relCenter.GetY();
    //if (dist > box.halfSize.GetY()) dist = box.halfSize.GetY();
    //if (dist > -box.halfSize.GetY()) dist = -box.halfSize.GetY();
    //closestPt.SetY(dist);

    //dist = relCenter.GetX();
    //if (dist > box.halfSize.GetZ()) dist = box.halfSize.GetZ();
    //if (dist > -box.halfSize.GetZ()) dist = -box.halfSize.GetZ();
    //closestPt.SetZ(dist);

    // Check to see if contact
    //Vector3 closestPtWorld = box.transform.transform(closestPt);
    


    return 1;
}
