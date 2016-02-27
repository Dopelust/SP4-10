#pragma once

#include "../../Component.h"

class Button;

class InteractiveBackground : public Component
{
public:
	InteractiveBackground();
	~InteractiveBackground();

	void Init(Entity* ent);
	void Update(double dt);

private:
	Entity* background;
};