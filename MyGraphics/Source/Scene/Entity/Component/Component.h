#ifndef COMPONENT_H
#define COMPONENT_H

#include "Mtx44.h"

struct Collision;
class Entity;

class Component
{
public:
	bool IsActive();
	void SetActive(bool active);

protected:
	friend Entity;

	Component();
	virtual ~Component() = 0;

	virtual void Init(Entity* ent);
	virtual void Update(double dt);
	virtual void Draw(const Mtx44& parent);
	
	virtual void OnCollisionEnter(const Collision& col);

	bool active;
};

#endif