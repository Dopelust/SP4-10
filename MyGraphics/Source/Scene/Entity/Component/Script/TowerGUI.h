#pragma once

#include "../Component.h"

#include <map>
using namespace::std;

class Button;
class TowerData;
class TowerManager;
class TextRenderer2D;

class TowerGUI : public Component
{
public:
	Button* upgrade;

	TextRenderer2D* name;
	TextRenderer2D* damage;
	TextRenderer2D* range;
	TextRenderer2D* cost;

	void Init(Entity* ent);
	void Update(double dt);

	void EnableUpgrades();
	void DisableUpgrades();

	void ShowInfo(const char* type, TowerData* tower);
	void AddButton(const char* key, Button* button);

private:
	map<string, Button*> button;
	TowerManager* manager;
};