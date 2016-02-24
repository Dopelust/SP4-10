#pragma once

#include "../Component.h"

class ScaleScript : public Component
{
public:
	ScaleScript();
	~ScaleScript();

	float rate;

	void Init(Entity* ent);
	void Update(double dt);

private:
	Entity* owner;
};