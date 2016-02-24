#pragma once

#include "../Component.h"

class FadeScript : public Component
{
public:
	FadeScript();
	~FadeScript();

	float rate;
	float* value;

	void Init(Entity* ent);
	void Update(double dt);

private:
	Entity* owner;
};