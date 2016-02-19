#pragma once

#include "../Component.h"

#include <map>
#include <string>
using namespace::std;

class StageManager;
struct Vector3;
class Transform;
class TowerPlacerGUI;
class TileSelector;
class Graphic2D;
class TowerInfoGUI;
struct TowerData;

class TowerPlacer : public Component
{
public:
	TowerPlacer();
	~TowerPlacer();

	StageManager* stage;
	TileSelector* selector;
	TowerInfoGUI* info;

	Entity* range;

	void Init(Entity* ent);
	void Update(double dt);
	void ShowIndicator(bool show, bool turret = false);
	void ShowInfo(TowerData* tower = NULL);

	bool IsPlacing();
	Entity* GetTower(const Vector3& position);

private:
	friend TowerPlacerGUI;

	string type;

	Transform* transform;
	Graphic2D* graphic;

	map<Vector3, Entity*> towerMap;
};