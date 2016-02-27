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
class BoxCollider;

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
	void SellTower();

	void SetToPlace(const char* type);
	void CancelPlacement();

	bool IsPlacing();
	bool CanPlace(Tile* tile);

	bool PlaceTower();

	Entity* GetTower(const Vector3& position);

	void Load(const char* filepath);
	void Save(const char* filepath);

private:
	string type;

	Transform* transform;
	BoxCollider* box;
	Graphic2D* graphic;

	Entity* selection;
	map<Vector3, Entity*> towerMap;
};