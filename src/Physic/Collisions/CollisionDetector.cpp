#include "CollisionDetector.h"



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
    Contact *contact = new Contact(sphere.body, 1, -sphereDistance, plane.getNormal());
    contact->m_contactPoint = position - plane.getNormal() * (sphereDistance + sphere.radius);

    data->addContact(contact);
    return 1;
}

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
    if (size <= 0.0f || size >= sphere1.radius + sphere2.radius) {
        return 0;
    }

    // 2. Générer un contact :
    //• Normal :                norme de la distance entre les deux sphères;
    //• Interpénétration :      somme des rayons moins la distance entre le centre des sphères.
    //• Le point de contact :   un point sur la surface d’une des sphères dans la direction du contact
    // Creating the normal
    Vector3 normal = midline * float((1.0f / size));
    // contacts.....
    Contact *contact = new Contact(sphere1.body, sphere2.body, 1, (sphere1.radius + sphere2.radius - size));
    contact->m_contactNormal = normal;
    contact->m_contactPoint = positionOne + midline * 0.5f;

    return 1;
}

unsigned CollisionDetector::boxAndHalfSpace(
        const Box &box,
        const Plane &plane,
        CollisionData *data) {

    // check intersection with bounding sphere of the box
    Vector3 testBoxInPlan = (box.getCenter() + box.halfSize.GetMaxValue() * plane.getNormal() * -1);
    float test = testBoxInPlan.DotProduct(plane.getNormal());
    if (test > plane.getOffset()) return 0;


    //
    static float mults[8][3] = {{1,  1,  1},
                                {-1, 1,  1},
                                {1,  -1, 1},
                                {-1, -1, 1},
                                {1,  1,  -1},
                                {-1, 1,  -1},
                                {1,  -1, -1},
                                {-1, -1, -1}};


    unsigned contactsUsed = 0;
    for (unsigned i = 0; i < 8; i++) {

        // Calculate the position of each vertex
        Vector3 vertexPos(mults[i][0], mults[i][1], mults[i][2]);
        vertexPos = vertexPos * box.halfSize;
        vertexPos = box.body->GetPointInWorldSpace(vertexPos);

        // Calculate the distance from the plane
        float vertexDistance = vertexPos.DotProduct(plane.getNormal() * -1);

        // Compare this to the plane's distance
        if ((vertexDistance - plane.getOffset()) > 0) {
            // Create the contact data.

            // The contact point is halfway between the vertex and the
            // plane - we multiply the direction by half the separation
            // distance and add the vertex location.

            Contact *contact = new Contact(box.body, plane.body,
                                           1,
                                           (vertexDistance - plane.getOffset())
            );
            contact->m_contactNormal = plane.getNormal();
            // To extrapolate on plane
            //contact->m_contactPoint = plane.getNormal();
            //contact->m_contactPoint *= (-plane.getOffset() + vertexDistance);
            //contact->m_contactPoint += vertexPos;
            // otherwise, this is the vertex Position of the box
            contact->m_contactPoint = vertexPos;

            data->addContact(contact);

            contactsUsed++;
        }
    }

    return contactsUsed;
}

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
        relCenter.GetZ() - sphere.radius > box.halfSize.GetZ()) {
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

    Contact *contact = new Contact(box.body, sphere.body, 1, sphere.radius - sqrt(dist));
    contact->m_contactNormal = Vector3(closestPtWorld - center);
    contact->m_contactNormal.Normalize();
    contact->m_contactPoint = closestPtWorld;

    data->addContact(contact);


    return 1;
}
