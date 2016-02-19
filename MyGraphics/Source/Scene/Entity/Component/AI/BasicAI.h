#pragma once

#include "../Component.h"

class RigidBody2D;
class Transform;
class BasicAI : public Component
{
public:
	Entity* target;

	BasicAI();
	~BasicAI();

	void Init(Entity* ent);
	void Update(double dt);

private:
	Transform* transform;
	RigidBody2D* rigid;
};