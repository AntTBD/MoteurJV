#include "CollisionDetector.h"


static inline float transformToAxis(
    const Box &box,
    const Vector3 &axis
)
{
    float tempX = fabsf(axis.DotProduct(box.transform->GetAxis(0)));
    float tempY = fabsf(axis.DotProduct(box.transform->GetAxis(1)));
    float tempZ = fabsf(axis.DotProduct(box.transform->GetAxis(2)));
    return
        box.halfSize.GetX() * tempX +
        box.halfSize.GetY() * tempY +
        box.halfSize.GetZ() * tempZ;
}

/*
static inline float penetrationOnAxis(
    const Box &box1,
    const Box &box2,
    const Vector3& axis,
    const Vector3& toCentre
)
{
    // Project the half-size of one onto axis
    float oneProject = transformToAxis(box1, axis);
    float twoProject = transformToAxis(box2, axis);

    // Project this onto the axis
    float distance = fabs(toCentre.DotProduct(axis));

    // Return the overlap (i.e. positive indicates
    // overlap, negative indicates separation).
    return oneProject + twoProject - distance;
}







static inline bool tryAxis(
    const Box &box1,
    const Box &box2,
    Vector3 axis,
    const Vector3& toCentre,
    unsigned index,

    // These values may be updated
    float& smallestPenetration,
    unsigned &smallestCase
)
{
    // Make sure we have a normalized axis, and don't check almost parallel axes
    if (axis.Magnitude() < 0.0001) return true;
    axis.Normalize();

    float penetration = penetrationOnAxis(box1, box2, axis, toCentre);

    if (penetration < 0) return false;
    if (penetration < smallestPenetration) {
        smallestPenetration = penetration;
        smallestCase = index;
    }
    return true;
}
*/


unsigned CollisionDetector::sphereAndHalfSpace(
        const Sphere &sphere,
        const Plane &plane,
        CollisionData *data) {

    // Sphere position
    Vector3 position = sphere.transform->GetAxis(3);

    // 1. Trouver la distance entre la sphère et le plan (prendre en compte le rayon)
    // Find the distance from the plane
    float sphereDistance = plane.getNormal().DotProduct(position) - sphere.radius - plane.getOffset();
    // Si la distance est positive, il n’y a pas de contact
    if (sphereDistance >= 0) return 0;

    // 2. Générer le contact avec :
    //• Normal :                direction du plan;
    //• Interpénétration :      distance entre la sphère et le plan;
    //• Le point de contact :   Le point sur la sphère en direction du contact.
    // Create the contact ; it has normal in the plane direction
    Contact* contact = new Contact(sphere.body, 1, -sphereDistance, plane.getNormal());
    contact->m_contactPoint = position - plane.getNormal() * (sphereDistance + sphere.radius);

    data->addContact(contact);
    return 1;
}

/*unsigned CollisionDetector::sphereAndTruePlane(
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
}*/

unsigned CollisionDetector::sphereAndSphere(
    const Sphere& sphere1,
    const Sphere& sphere2,
    CollisionData* data) {

    // Sphere positions
    Vector3 positionOne = sphere1.transform->GetAxis(3);
    Vector3 positionTwo = sphere2.transform->GetAxis(3);

    // 1. Calculer la distance entre les deux sphères
    // Find the vector between the objects
    Vector3 midline = positionOne - positionTwo;

    // Si la distance au carré est plus petite que la somme des rayons au carré, il n’y a pas de collision.
    float size = midline.Magnitude();
    // See if it is large enough
    if (size <= 0.0f || size >= sphere1.radius + sphere2.radius) 
    {
        return 0;
    }

    // 2. Générer un contact :
    //• Normal :                norme de la distance entre les deux sphères;
    //• Interpénétration :      somme des rayons moins la distance entre le centre des sphères.
    //• Le point de contact :   un point sur la surface d’une des sphères dans la direction du contact
    // Creating the normal
    Vector3 normal = midline * float((1.0f/size));
    // contacts.....
    Contact* contact = new Contact(sphere1.body, sphere2.body, 1, (sphere1.radius+sphere2.radius - size));
    contact->m_contactNormal = normal;
    contact->m_contactPoint = positionOne + midline * 0.5f;



    return 1;
}

bool CollisionDetector::IntersectionTestsBoxAndHalfSpace(
        const Box &box,
        const Plane &plane
)
{
    Vector3 normPlan = plane.getNormal();
    // Work out the projected radius of the box onto the plane direction
    float projectedRadius = transformToAxis( box, normPlan);

    // Work out how far the box is from the origin
    float boxDistance =
            normPlan.DotProduct(box.body->GetOrientation().ToEulerInDegrees()) - projectedRadius;

    // Check for the intersection
    return boxDistance <= plane.getOffset();
}

unsigned CollisionDetector::boxAndHalfSpace(
        const Box &box,
        const Plane &plane,
        CollisionData *data) {

    // check for intersection
   /* if (!CollisionDetector::IntersectionTestsBoxAndHalfSpace(box, plane))
    {
        return 0;
    }*/
   // check intersection with bounding sphere of the box
   Vector3 testBoxInPlan = (box.getCenter()+box.halfSize.GetMaxValue()*plane.getNormal()*-1);
   float test = testBoxInPlan.DotProduct(plane.getNormal());
    if(test >  plane.getOffset()) return 0;


    //
    static float mults[8][3] = { {1,1,1},{-1,1,1},{1,-1,1},{-1,-1,1},
                                 {1,1,-1},{-1,1,-1},{1,-1,-1},{-1,-1,-1} };


    unsigned contactsUsed = 0;
    for (unsigned i = 0; i < 8; i++) {

        // Calculate the position of each vertex
        Vector3 vertexPos(mults[i][0], mults[i][1], mults[i][2]);
        vertexPos = vertexPos * box.halfSize;
        vertexPos = box.body->GetPointInWorldSpace(vertexPos);

        // Calculate the distance from the plane
        float vertexDistance = vertexPos.DotProduct(plane.getNormal()*-1);

        // Compare this to the plane's distance
        if ((vertexDistance - plane.getOffset()) > 0 )
        {
            // Create the contact data.

            // The contact point is halfway between the vertex and the
            // plane - we multiply the direction by half the separation
            // distance and add the vertex location.

            Contact* contact = new Contact(box.body, plane.body,
                                           1,
                                           (vertexDistance - plane.getOffset())
                                           );
            contact->m_contactNormal = plane.getNormal()*-1;
            contact->m_contactPoint = plane.getNormal()*-1;
            contact->m_contactPoint *= (-plane.getOffset()+vertexDistance);
            contact->m_contactPoint += vertexPos;

            data->addContact(contact);

            contactsUsed++;
        }
    }

    return contactsUsed;
}

/*#define CHECK_OVERLAP(axis,index)\
    if (!tryAxis(box1, box2, (axis), toCentre, (index), pen, best)) return 0;


unsigned CollisionDetector::boxAndBox(
        const Box &box1,
        const Box &box2,
        CollisionData *data) {
    // Find the vector between the two centres 
    Vector3 toCentre = box2.transform->GetAxis(3) - box1.transform->GetAxis(3);

    // we start assuming there is no contact
    float pen = FLT_MAX;
    unsigned best = 0xffffff;

    // Now we check each axes, returning if it gives us a separating axis, and keeping track of the axis 
    // with the smallest penetration otherwise
    CHECK_OVERLAP(box1.transform->GetAxis(0).GetX(), 0);
    CHECK_OVERLAP(box1.transform->GetAxis(1).GetY(), 1);
    CHECK_OVERLAP(box1.transform->GetAxis(2).GetZ(), 2);

    CHECK_OVERLAP(box2.transform->GetAxis(0).GetX(), 3);
    CHECK_OVERLAP(box2.transform->GetAxis(1).GetY(), 4);
    CHECK_OVERLAP(box2.transform->GetAxis(2).GetZ(), 5);

//...

    return 0;
}

unsigned CollisionDetector::boxAndPoint(
        const Box &box,
        const Vector3 &point,
        CollisionData *data) {
    return 0;
}*/

unsigned CollisionDetector::boxAndSphere(
        const Box &box,
        const Sphere &sphere,
        CollisionData *data) {
    // 1. Convertir le centre du cercle en coordonné de la boîte
    Vector3 center = sphere.transform->GetAxis(3);
    Vector3 relCenter = box.body->GetPointInLocalSpace(center);

    // Early out check to see if we can exclude the contact. 
    if (relCenter.GetX() - sphere.radius > box.halfSize.GetX() ||
        relCenter.GetY() - sphere.radius > box.halfSize.GetY() ||
        relCenter.GetZ() - sphere.radius > box.halfSize.GetZ())
    {
        return 0;
    }

    Vector3 closestPt(0, 0, 0);
    float dist;

    // 2. Resserrer les coordonnés du point par rapport à la boîte
    dist = relCenter.GetX();
    if (dist > box.halfSize.GetX()) dist = box.halfSize.GetX();
    if (dist > -box.halfSize.GetX()) dist = -box.halfSize.GetX();
    closestPt.SetX(dist);

    dist = relCenter.GetY();
    if (dist > box.halfSize.GetY()) dist = box.halfSize.GetY();
    if (dist > -box.halfSize.GetY()) dist = -box.halfSize.GetY();
    closestPt.SetY(dist);

    dist = relCenter.GetZ();
    if (dist > box.halfSize.GetZ()) dist = box.halfSize.GetZ();
    if (dist > -box.halfSize.GetZ()) dist = -box.halfSize.GetZ();
    closestPt.SetZ(dist);

    
    // 3. À l’aide de ce point, il est possible d’extraire les données de contacts
    // Check to see if contact
    dist = (closestPt - relCenter).Magnitude();
    if (dist > sphere.radius * sphere.radius) return 0;


    Vector3 closestPtWorld = box.body->GetPointInWorldSpace(closestPt);

    Contact* contact = new Contact(box.body, sphere.body, 1, sphere.radius - sqrt(dist));
    contact->m_contactNormal = Vector3(closestPtWorld - center);
    contact->m_contactNormal.Normalize();
    contact->m_contactPoint = closestPtWorld;

    data->addContact(contact);


    return 1;
}
