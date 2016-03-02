#pragma once

#include "../Component.h"

class Button;
class Popup;

class CanvasUI : public Component
{
public:
	CanvasUI();

	void SetFocus(Button* focus);
	Button* GetFocus();

	void SetPopup(Popup* popup);
	void ClosePopup();
	Popup* GetPopup();

	void Init(Entity* ent);
	void Update(double dt);

private:
	Popup* popup;
	Button* focus;
};