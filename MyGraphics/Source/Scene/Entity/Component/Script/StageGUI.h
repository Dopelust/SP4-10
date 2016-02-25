#pragma once

#include "../Component.h"

class TextRenderer2D;
class StageManager;

class StageGUI : public Component
{
public:
	StageGUI();
	~StageGUI();

	void Init(Entity* ent);
	void Update(double dt);

private:
	StageManager* stage;

	TextRenderer2D* wave;
	TextRenderer2D* timer;
};