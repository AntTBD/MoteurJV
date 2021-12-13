#include "Sphere.h"

float Sphere::distancePoint(Vector3 point)
{
	Vector3 distance = Vector3();

	

	return sqrt(pow(point.GetX() - centre.GetX(), 2) + pow(point.GetX() - centre.GetX(), 2) + pow(point.GetX() - centre.GetX(), 2)) - radius;
}
