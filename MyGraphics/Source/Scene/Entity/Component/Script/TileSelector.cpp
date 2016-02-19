#include "TileSelector.h"

#include "Vector2.h"
#include "../../../../InputHandler.h"
#include "../../../../Grid.h"
#include "../../../../Tile.h"

#include "../../../Scene.h"
#include "../GUI/Canvas.h"

#include "../Transform.h"
#include "../../Entity.h"

TileSelector::TileSelector()
{
}

TileSelector::~TileSelector()
{
}

Tile* TileSelector::GetSelection()
{
	return tile;
}

void TileSelector::Init(Entity* entity)
{
	transform = entity->transform;
}

void TileSelector::Update(double dt)
{
	Vector3 index = Scene::scene->grid->GetIndex(Scene::scene->camera.position + Input.GetCursorPos().GetVector3());
	transform->Position() = (index + Vector3(0.5f, 0.5f)) * Vector2(TileWidth, TileHeight).GetVector3();

	if (Canvas.GetFocus())
		tile = NULL;
	else
		tile = Scene::scene->grid->GetTile(index.x, index.y);
}