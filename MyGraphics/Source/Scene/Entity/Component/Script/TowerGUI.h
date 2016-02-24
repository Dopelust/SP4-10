#pragma once

#include "../Component.h"

#include <map>
using namespace::std;

class Button;
struct TowerData;
class TowerManager;
class TextRenderer2D;
class SpriteRenderer;

class TowerGUI : public Component
{
public:
	SpriteRenderer* rank;

	TextRenderer2D* cost;
	Button* upgrade;

	TextRenderer2D* sellprice;
	Button* sell;

	TextRenderer2D* name;

	TextRenderer2D* damage;
	TextRenderer2D* range;
	TextRenderer2D* force;
	TextRenderer2D* speed;
	TextRenderer2D* projectiles;

	void Init(Entity* ent);
	void Update(double dt);

	void EnableSale();
	void DisableSale();

	void EnableUpgrades();
	void DisableUpgrades();

	void ShowInfo(const char* type, int rank = 0);
	void AddButton(const char* key, Button* button);

private:
	map<string, Button*> button;
	TowerManager* manager;
};