#pragma once

#include "../Component.h"

class Toggle;
class Checkbox : public Component
{
public:
	Checkbox();
	~Checkbox();

	Entity* check;

	bool IsCheck();
	void SetCheck(bool check);

	void Init(Entity* ent);
	void Update(double dt);

private:
	Toggle* toggle;
};