#pragma once

#include "../Component.h"

#include <map>
using namespace::std;

class Transform;
class TowerPlacer;
class Button;

class TowerPlacerGUI : public Component
{
public:
	TowerPlacerGUI();
	~TowerPlacerGUI();

	void Init(Entity* ent);
	void Update(double dt);

	void AddButton(const char* key, Button* button);

private:
	map<string, Button*> button;
	TowerPlacer* placer;
};