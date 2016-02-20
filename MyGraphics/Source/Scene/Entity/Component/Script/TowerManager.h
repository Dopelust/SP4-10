#pragma once

#include "../Component.h"

#include <map>
#include <string>
using namespace::std;

class Tile;
class StageManager;
struct Vector3;
class Transform;
class TowerPlacerGUI;
class TileSelector;
class Graphic2D;
class TowerGUI;
struct TowerData;

class TowerManager : public Component
{
public:
	TowerManager();
	~TowerManager();

	StageManager* stage;
	TileSelector* selector;
	TowerGUI* gui;

	Entity* range;

	void Init(Entity* ent);
	void Update(double dt);

	void ShowIndicator(bool shadow = true);
	void HideIndicator();

	void ShowInfo(Entity* tower);
	void ShowInfo(string type);
	void HideInfo();

	void Unselect();
	void Select(Entity* tower);
	void UpgradeTower();

	void SetToPlace(const char* type);
	void CancelPlacement();

	bool IsPlacing();
	bool CanPlace(Tile* tile);

	bool PlaceTower();

	Entity* GetTower(const Vector3& position);

private:
	string type;

	Transform* transform;
	Graphic2D* graphic;

	Entity* selection;
	map<Vector3, Entity*> towerMap;
};