#pragma once

#include "../Component.h"

#include "Vector2.h"

class Transform;
class TileEditorGUI;
class TileSelector;
class Graphic2D;

class TileEditor : public Component
{
public:
	TileEditor();
	~TileEditor();

	void Init(Entity* ent);
	void Update(double dt);

private:
	friend TileEditorGUI;

	Graphic2D* graphic;
	TileSelector* selector;

	Vector2 snap;
	int index;
};