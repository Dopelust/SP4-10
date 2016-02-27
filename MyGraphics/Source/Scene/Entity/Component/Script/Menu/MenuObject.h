#pragma once

#include "../../Component.h"
#include "Vector2.h"

class Transform;
class MenuHandler;

class MenuObject : public Component
{
public:
	MenuObject();
	~MenuObject();

	MenuHandler* menu;

	virtual void Init(Entity* ent);
	virtual void Update(double dt);

	void Appear();
	void Disappear();

protected:
	float rate;
	bool appear;
	Vector2 position, target;

	Transform* transform;
};