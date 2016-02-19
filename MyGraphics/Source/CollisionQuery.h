#pragma once

struct Vector3;
class BoxCollider;
class CollisionQuery
{
public:
	static bool Test(BoxCollider* a, BoxCollider* b);
	static bool Test(BoxCollider* a, const Vector3& minB, const Vector3& maxB);
	static bool Test(const Vector3& minA, const Vector3& maxA, const Vector3& minB, const Vector3& maxB);

	static bool Test(BoxCollider* box, const Vector3& position, float radius);

	static float PenetrationDepth(const Vector3& minA, const Vector3& maxA, const Vector3& minB, const Vector3& maxB);
};
