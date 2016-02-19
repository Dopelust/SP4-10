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
				if (tower)
					tower->GetComponent<Graphic2D>()->SetColor(1, 1, 1, 1);

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
	{
		if (tower)
			tower->GetComponent<Graphic2D>()->SetColor(1, 1, 1, 1);

		tower = NULL;
	}

	if (tower)
	{
		placer->ShowIndicator(true, true);
		placer->ShowInfo(tower->GetComponent<TowerController>()->GetData());
		tower->GetComponent<Graphic2D>()->SetColor(2,2,2,1);

		transform->Position() = tower->transform->GetPosition();
	}
}