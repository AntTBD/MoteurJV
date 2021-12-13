#include "Plane.h"

float Plane::distancePoint(Vector3 point)
{
	return normal.Normalize().DotProduct(point);
}
