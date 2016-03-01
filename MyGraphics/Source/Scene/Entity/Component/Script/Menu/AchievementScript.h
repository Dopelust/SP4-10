#pragma once

#include "StateObject.h"
#include "../StageManager.h"

#include <vector>

using std::vector;

class Checkbox;
class Slider;
class Button;
class TextRenderer2D;

class AchievementScript : public StateObject
{
public:
	AchievementScript();
	~AchievementScript();

	void Init(Entity* ent);
	void Update(double dt);

	void LoadAchievements(const char *filepath);

private:
	void ResetAchievements();
	void UpdateAchievements();

	Button* back;
	Button* reset;

	Achievement achievement;

	vector<TextRenderer2D*> texts;
};