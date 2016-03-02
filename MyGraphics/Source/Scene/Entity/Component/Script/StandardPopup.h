#pragma once

#include "../Component.h"

class TextRenderer2D;
class Button;
class Popup;

class StandardPopup : public Component
{
public:
	StandardPopup();
	~StandardPopup();

	void PopUp(const char* text);
	void Close();

	bool IsOK();
	bool IsCancel();

	TextRenderer2D* text;
	Button* ok;
	Button* cancel;
	Button* close;

	void Init(Entity* ent);
	void Update(double dt);

private:
	Popup* popup;
};