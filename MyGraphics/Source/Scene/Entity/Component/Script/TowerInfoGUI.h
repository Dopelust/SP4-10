#pragma once

#include "../Component.h"

#include <map>
using namespace::std;

class Transform;
class TowerData;
class TextRenderer2D;

class TowerInfoGUI : public Component
{
public:
	TextRenderer2D* damage;
	TextRenderer2D* range;
	TextRenderer2D* cost;

	void ShowInfo(TowerData* tower);
};