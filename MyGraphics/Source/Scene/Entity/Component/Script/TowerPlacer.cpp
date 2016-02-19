#include "TowerPlacer.h"
#include "TileSelector.h"
#include "TowerInfoGUI.h"

#include "../../../../InputHandler.h"
#include "../../../../Grid.h"
#include "../../../../Tile.h"

#include "../../../Scene.h"
#include "../Transform.h"
#include "../../Entity.h"
#include "../Graphic2D.h"

TowerPlacer::TowerPlacer()
{
}

TowerPlacer::~TowerPlacer()
{
}

void TowerPlacer::Init(Entity* entity)
{
	transform = entity->transform;
	graphic = entity->GetComponent<Graphic2D>();
}

#include "../../EntityFactory.h"
#include "../../../Tower/TowerDatabase.h"

bool TowerPlacer::IsPlacing()
{
	return !type.empty();
}

#include "StageManager.h"

void TowerPlacer::Update(double dt)
{
	Tile* tile = selector->GetSelection();

	if (tile)
	{
		if (Input.IsMousePress(1))
		{
			type = "";

			ShowIndicator(false);
			ShowInfo(NULL);
		}
		else
		{
			if (type.empty())
			{
				ShowIndicator(false);
			}
			else
			{
				if (!tile->index && !GetTower(transform->GetPosition()))
				{
					graphic->SetColor(0.5f, 1, 0.5f, 0.5f);

					if (Input.IsMousePress(0))
					{
						Input.ApplyMouseBuffer(0);

						towerMap[transform->GetPosition()] = EntityFactory::GenerateTower(transform->GetPosition().GetVector2(), type);
						type = "";
						ShowInfo(NULL);

						Vector3 index = Scene::scene->grid->GetIndex(transform->GetPosition());
						stage->AddObstruction(index.x, index.y);
					}
				}
				else
				{
					graphic->SetColor(1, 0.2f, 0.2f, 0.5f);
				}

				ShowIndicator(true);
			}
		}
	}
	else
		ShowIndicator(false);
}

void TowerPlacer::ShowIndicator(bool show, bool turret)
{
	graphic->SetActive(show);
	range->SetActive(show);

	if (show)
	{
		transform->Position() = selector->transform->GetPosition();
	}

	if (turret)
	{
		graphic->SetActive(false);
	}
}

void TowerPlacer::ShowInfo(TowerData* tower)
{
	info->ShowInfo(tower);

	if (tower)
		range->transform->SetSize(tower->range * 2, tower->range * 2);
}

Entity*  TowerPlacer::GetTower(const Vector3& position)
{
	if (towerMap.find(position) != towerMap.end())
		return towerMap[position];

	return NULL;
}