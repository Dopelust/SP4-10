#pragma once

#include "StateObject.h"

class Checkbox;
class Slider;
class Button;

class OptionScript : public StateObject
{
public:
	OptionScript();
	~OptionScript();

	void Init(Entity* ent);
	void Update(double dt);

	void SaveOptions();

private:
	Button* back;

	Slider* bgm;
	Checkbox* muteBGM;
	Slider* sfx;
	Checkbox* muteSFX;
};