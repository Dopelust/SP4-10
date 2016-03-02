#include "TileEditor.h"
#include "TileSelector.h"

#include "Vector2.h"
#include "../../../../InputHandler.h"
#include "../../../../Grid.h"
#include "../../../../Tile.h"

#include "../../../Scene.h"
#include "../Transform.h"
#include "../../Entity.h"
#include "../SpriteRenderer.h"

#include "../GUI/Canvas.h"

TileEditor::TileEditor() : index(0)
{
}

TileEditor::~TileEditor()
{
}

void TileEditor::Init(Entity* entity)
{
	selector = entity->GetComponent<TileSelector>();
	sprite = entity->GetComponent<SpriteRenderer>();
}

void TileEditor::Update(double dt)
{
	if (Canvas.GetPopup())
		return;

	Tile* tile = NULL;

	if (Input.IsMousePress(1))
		snap = Input.GetCursorPos();
	else if (Input.IsMouseHeld(1))
	{
		Scene::scene->camera.position -= (Input.GetCursorPos() - snap).GetVector3();
		snap = Input.GetCursorPos();
	}
	else
		tile = selector->GetSelection();

	if (tile)
	{
		if (Input.IsMouseHeld(0))
			tile->index = index;

		sprite->SetActive(true);
	}
	else
		sprite->SetActive(false);
}