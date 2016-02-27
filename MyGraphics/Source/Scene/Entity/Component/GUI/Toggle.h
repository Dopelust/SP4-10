#pragma once

#include "../Component.h"

class Button;
class Toggle : public Component
{
public:
	Toggle();
	~Toggle();

	bool IsToggled();
	void SetToggle(bool toggle);

	void Init(Entity* ent);
	void Update(double dt);
private:
	Button* button;
	bool toggle;
};