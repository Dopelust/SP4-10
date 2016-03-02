#pragma once

#include "../Component.h"

class TextRenderer2D;
class Button;
class Popup;

class SimplePopup : public Component
{
public:
	SimplePopup();
	~SimplePopup();

	void PopUp(const char* text);
	void Close();

	bool IsOK();
	
	TextRenderer2D* text;
	Button* ok;

	void Init(Entity* ent);
	void Update(double dt);

private:
	Popup* popup;
};