#pragma once

#include "../Component.h"

class TextRenderer2D;
class StageManager;
class Button;

class StageGUI : public Component
{
public:
	StageGUI();
	~StageGUI();

	void Init(Entity* ent);
	void Update(double dt);

	bool ButtonPress();
	void SetPopup(const char* text);

private:
	StageManager* stage;

	Button* pause;
	
	TextRenderer2D* popup;

	TextRenderer2D* health;
	TextRenderer2D* gold;

	TextRenderer2D* wave;
	TextRenderer2D* timer;
};