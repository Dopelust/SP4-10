#pragma once

#include "../Component.h"

#include "Vector2.h"

class Transform;
class TileEditorGUI;
class TileSelector;
class SpriteRenderer;

class TileEditor : public Component
{
public:
	TileEditor();
	~TileEditor();

	void Init(Entity* ent);
	void Update(double dt);

private:
	friend TileEditorGUI;

	SpriteRenderer* sprite;
	TileSelector* selector;

	Vector2 snap;
	int index;
};