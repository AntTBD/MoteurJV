#pragma once

#include "Vector3.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Bounding Sphere 
typedef struct BoundingSphere {

	Vector3 center = Vector3();
	float radius = 0;


    BoundingSphere() {
        center = Vector3();
        radius = 0;
    }

    BoundingSphere(const Vector3 &center, float radius)
    {
        this->center = center;
        this->radius = radius;
    }
    BoundingSphere(const BoundingSphere &one,
                   const BoundingSphere &two)
    {
        Vector3 centreOffset = two.center - one.center;
        float distance = centreOffset.Magnitude();
        float radiusDiff = two.radius - one.radius;

        // Check if the larger sphere encloses the small one
        if (radiusDiff >= distance)
        {
            if (one.radius > two.radius)
            {
                center = one.center;
                radius = one.radius;
            }
            else
            {
                center = two.center;
                radius = two.radius;
            }
        }

            // Otherwise we need to work with partially
            // overlapping spheres
        else
        {
            radius = (distance + one.radius + two.radius) * 0.5f;

            // The new centre is based on one's centre, moved towards
            // two's centre by an ammount proportional to the spheres'
            // radii.
            center = one.center;
            if (distance > 0)
            {
                center += centreOffset * ((float)(radius - one.radius)/(float)distance);
            }
        }

    }

    //  (4/3) ? r3
    float getVolume() const{
        return (4.f / 3.f) * (float)M_PI * powf(radius,3);
    }


    float getGrowth(const BoundingSphere &other) const
    {
        BoundingSphere newSphere(*this, other);

        // We return a value proportional to the change in surface
        // area of the sphere.
        return powf(newSphere.radius,2) - powf(radius,2);
    }

    bool overlaps(const BoundingSphere &other) const{
        float distance = (this->center - other.center).Magnitude();
        return distance < this->radius + other.radius;
    }

}BoundingSphere;

