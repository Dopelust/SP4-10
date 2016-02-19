#include "TowerPicker.h"
#include "TowerPlacer.h"
#include "TileSelector.h"

#include "TowerInfoGUI.h"

#include "Vector2.h"
#include "../../../../InputHandler.h"
#include "../../../../Grid.h"
#include "../../../../Tile.h"

#include "../../../Scene.h"
#include "../Transform.h"
#include "../../Entity.h"
#include "../Graphic2D.h"

TowerPicker::TowerPicker() : tower(NULL)
{
}

TowerPicker::~TowerPicker()
{
}

void TowerPicker::Init(Entity* entity)
{
	transform = entity->transform;
	placer = entity->GetComponent<TowerPlacer>();
}

#include "../../EntityFactory.h"
#include "TowerController.h"

void TowerPicker::Update(double dt)
{
	if (!placer->IsPlacing())
	{
		if (Input.IsMousePress(0))
		{
			Tile* tile = placer->selector->GetSelection();

			if (tile)
			{
				tower = placer->GetTower(placer->selector->transform->GetPosition());

				if (!tower)
				{
					placer->ShowIndicator(false);
					placer->ShowInfo(NULL);
				}
			}
		}
	}
	else
		tower = NULL;

	if (tower)
	{
		placer->ShowIndicator(true);
		placer->ShowInfo(tower->GetComponent<TowerController>()->GetData());

		transform->Position() = tower->transform->GetPosition();
	}
}