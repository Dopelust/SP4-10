#include "CollisionQuery.h"

#include "Scene\Entity\Component\Physics\BoxCollider.h"

bool CollisionQuery::Test(BoxCollider * a, BoxCollider * b)
{
	return Test(a->GetMinCoord(), a->GetMaxCoord(), b->GetMinCoord(), b->GetMaxCoord());
}

bool CollisionQuery::Test(BoxCollider * a, const Vector3 & minB, const Vector3 & maxB)
{
	return Test(a->GetMinCoord(), a->GetMaxCoord(), minB, maxB);
}

bool CollisionQuery::Test(const Vector3 & minA, const Vector3 & maxA, const Vector3 & minB, const Vector3 & maxB)
{
	return minA.x < maxB.x && maxA.x > minB.x && minA.y < maxB.y && maxA.y > minB.y && minA.z <= maxB.z && maxA.z >= minB.z;
}

bool CollisionQuery::Test(BoxCollider * box, const Vector3 & position, float radius)
{
	Vector3 point = position;
	
	Vector3& min = box->GetMinCoord();
	Vector3& max = box->GetMaxCoord();

	if (point.x > max.x) point.x = max.x;
	if (point.x < min.x) point.x = min.x;
	if (point.y > max.y) point.y = max.y;
	if (point.y < min.y) point.y = min.y;
	if (point.z > max.z) point.z = max.z;
	if (point.z < min.z) point.z = min.z;

	return point.DistSquared(position) < radius * radius;
}

float CollisionQuery::PenetrationDepth(const Vector3& minA, const Vector3& maxA, const Vector3& minB, const Vector3& maxB)
{
	if (Test(minA, maxA, minB, maxB))
	{
		Vector3 PenetrationDepth;

		if (maxA.x > maxB.x && minA.x > minB.x)
			PenetrationDepth.x = maxB.x - minA.x;

		else if (maxA.x < maxB.x && minA.x < minB.x)
			PenetrationDepth.x = maxA.x - minB.x;

		else if (minA.x >= minB.x && maxA.x <= maxB.x)
			PenetrationDepth.x = maxA.x - minA.x;

		else if (minA.x <= minB.x && maxA.x >= maxB.x)
			PenetrationDepth.x = maxA.x - minA.x;

		if (maxA.y > maxB.y && minA.y > minB.y)
			PenetrationDepth.y = maxB.y - minA.y;

		else if (maxA.y < maxB.y && minA.y < minB.y)
			PenetrationDepth.y = maxA.y - minB.y;

		else if (minA.y >= minB.y && maxA.y <= maxB.y)
			PenetrationDepth.y = maxA.y - minA.y;

		else if (minA.y <= minB.y && maxA.y >= maxB.y)
			PenetrationDepth.y = maxA.y - minA.y;

		if (maxA.z > maxB.z && minA.z > minB.z)
			PenetrationDepth.z = maxB.z - minA.z;

		else if (maxA.z < maxB.z && minA.z < minB.z)
			PenetrationDepth.z = maxA.z - minB.z;

		else if (minA.z >= minB.z && maxA.z <= maxB.z)
			PenetrationDepth.z = maxA.z - minA.z;

		else if (minA.z <= minB.z && maxA.z >= maxB.z)
			PenetrationDepth.z = maxA.z - minA.z;

		return PenetrationDepth.x * PenetrationDepth.y * PenetrationDepth.z;
	}
	return 0;
}

