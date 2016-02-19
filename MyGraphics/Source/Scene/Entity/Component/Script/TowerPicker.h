#pragma once

#include "../Component.h"

class Transform;
class TowerPlacer;

class TowerPicker : public Component
{
public:
	TowerPicker();
	~TowerPicker();

	void Init(Entity* ent);
	void Update(double dt);

private:
	Transform* transform;

	Entity* tower;
	TowerPlacer* placer;
};