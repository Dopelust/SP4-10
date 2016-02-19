#pragma once

#include "../Component.h"

class Tile;
class Transform;

class TileSelector : public Component
{
public:
	TileSelector();
	~TileSelector();

	void Init(Entity* ent);
	void Update(double dt);

	Transform* transform;
	Tile* GetSelection();

private:
	Tile* tile;
};