#pragma once

#include "../../Component.h"
#include "Vector2.h"

class Transform;
class StateHandler;

class StateObject : public Component
{
public:
	StateObject();
	~StateObject();

	StateHandler* menu;

	Entity* owner;

	virtual void Init(Entity* ent);
	virtual void Update(double dt);

	void Appear();
	void Disappear(bool left);

	bool ReachedTarget();

protected:
	float rate;
	Vector2 target;

	Transform* transform;
};