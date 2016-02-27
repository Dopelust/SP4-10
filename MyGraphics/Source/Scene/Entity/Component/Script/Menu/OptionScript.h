#pragma once

#include "MenuObject.h"

class Checkbox;
class Slider;
class Button;

class OptionScript : public MenuObject
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