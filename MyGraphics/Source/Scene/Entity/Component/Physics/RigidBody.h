#pragma once

#include "../Component.h"
#include "Vector3.h"

class Grid;
class BoxCollider;
class Transform;

class RigidBody : public Component
{
public:
	RigidBody();
	~RigidBody();

	Vector3 velocity;
	bool ignoreCollisions;
	float mass, friction, bounceFactor, gravityScale;

	Vector3 GetHorizontalVelocity();

	void ApplyForce(const Vector3& force);

	void Init(Entity* ent);
	void Update(double dt);

	void ResolveCollisions();

protected:
	BoxCollider* box;
	Entity* owner;
	Transform* transform;

	Vector3 lastposition;
	Vector3 GetLastMaxCoord();
	Vector3 GetLastMinCoord();
};