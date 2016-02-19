#pragma once

#include "../Component.h"

class Button;

class CanvasUI : public Component
{
public:
	CanvasUI();

	void SetFocus(Button* focus);
	Button* GetFocus();

	void Init(Entity* ent);
	void Update(double dt);

private:
	Button* focus;
};