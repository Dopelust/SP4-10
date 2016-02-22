#include "TowerManager.h"
#include "TileSelector.h"
#include "TowerGUI.h"

#include "../../../../InputHandler.h"
#include "../../../../Grid.h"
#include "../../../../Tile.h"

#include "../../../Scene.h"
#include "../Transform.h"
#include "../../Entity.h"
#include "../Graphic2D.h"

TowerManager::TowerManager() : selection(NULL)
{
}

TowerManager::~TowerManager()
{
}

void TowerManager::Init(Entity* entity)
{
	transform = entity->transform;

	box = entity->GetComponent<BoxCollider>();

	graphic = entity->GetComponent<Graphic2D>();
	graphic->SetActive(false);
}

#include "../../EntityFactory.h"
#include "../../../Tower/TowerDatabase.h"
#include "TowerController.h"
#include "StageManager.h"

void TowerManager::SetToPlace(const char * type)
{
	Unselect();

	ShowIndicator(true);
	ShowInfo(type);

	this->type = type;
}

void TowerManager::CancelPlacement()
{
	HideIndicator();
	HideInfo();
	
	type = "";
}

bool TowerManager::IsPlacing()
{
	return !type.empty();
}

#include "../Physics/BoxCollider.h"
#include "../../../../Cell.h"
#include "../../../../CollisionQuery.h"

bool TowerManager::CanPlace(Tile* tile)
{
	if (tile)
	{
		if (!tile->index && !GetTower(selector->transform->GetPosition()))
		{
			for (auto& cell : box->GetCells())
			{
				for (auto& entity : cell->GetEntities())
				{
					if (entity->GetName() == "Enemy")
					{
						if (CollisionQuery::Test(box, entity->GetComponent<BoxCollider>()))
							return false;
					}
				}
			}

			return true;
		}
	}

	return false;
}

bool TowerManager::PlaceTower()
{
	Vector3& position = selector->transform->GetPosition();
	towerMap[position] = EntityFactory::GenerateTower(position.GetVector2(), type);

	Vector3& index = Scene::scene->grid->GetIndex(position);
	stage->AddObstruction((int)index.x, (int)index.y);

	type = "";
	HideInfo();
	HideIndicator();

	return true;
}

void TowerManager::Update(double dt)
{
	Tile* tile = selector->GetSelection();

	if (IsPlacing()) //Placing A Tower
	{
		if (Input.IsMousePress(1)) //If Right Click
		{
			CancelPlacement(); //Cancel Tower Placement
		}
		else
		{
			transform->Position() = selector->transform->GetPosition(); //Indicator Follow The Cursor

			if (CanPlace(tile)) //If Valid Spot
			{
				graphic->SetColor(0, 1, 0, 0.5f); //Change Indicator To Green

				if (Input.IsMousePress(0)) //If Left Click
				{
					PlaceTower(); //Place Tower
				}
			}
			else //If Invalid Spot
			{
				graphic->SetColor(1, 0, 0, 0.5f); //Change Indicator To Red
			}
		}
	}
	else
	{
		if (Input.IsMousePress(0))
		{
			if (tile) //If Hovering Over A Tile
				Unselect(); //Unselect Current Tower

			Entity* tower = GetTower(selector->transform->GetPosition()); //Get The Tower You Are Hovering

			if (tower) //If There Is A Tower
			{
				Select(tower); //Select The Tower
			}
			else //If There Is No Tower
			{

			}
		}
	}
}

void TowerManager::ShowIndicator(bool shadow)
{
	graphic->SetActive(shadow);
	range->SetActive(true);

	transform->Position() = selector->transform->GetPosition();
}

void TowerManager::HideIndicator()
{
	graphic->SetActive(false);
	range->SetActive(false);
}

void TowerManager::ShowInfo(Entity * tower)
{
	TowerData* data = tower->GetComponent<TowerController>()->GetData();

	gui->ShowInfo(tower->GetComponent<TowerController>()->type.c_str(), data);
	range->transform->SetSize((float)(data->range * 2), (float)(data->range * 2));
}

void TowerManager::ShowInfo(string type)
{
	TowerData* data = &TowerDatabase::GetData(type.c_str())[0];

	gui->ShowInfo(type.c_str(), data);
	range->transform->SetSize((float)(data->range * 2), (float)(data->range * 2));
}

void TowerManager::HideInfo()
{
	gui->ShowInfo("", NULL);
	gui->DisableUpgrades();
}

void TowerManager::Unselect()
{
	if (selection)
	{
		selection->GetComponent<Graphic2D>()->SetColor(1, 1, 1, 1);
		gui->DisableUpgrades();

		HideIndicator();
		HideInfo();

		this->selection = NULL;
	}
}

void TowerManager::Select(Entity * tower)
{
	this->selection = tower;

	if (tower->GetComponent<TowerController>()->IsMaxUpgrade())
		gui->DisableUpgrades();
	else
		gui->EnableUpgrades();

	tower->GetComponent<Graphic2D>()->SetColor(2, 2, 2, 1);

	ShowIndicator(false);
	ShowInfo(tower);
}

void TowerManager::UpgradeTower()
{
	if (selection)
	{
		TowerController* tower = selection->GetComponent<TowerController>();

		tower->Upgrade();
		ShowInfo(selection);

		if (tower->IsMaxUpgrade())
			gui->DisableUpgrades();
	}
}

Entity*  TowerManager::GetTower(const Vector3& position)
{
	if (towerMap.find(position) != towerMap.end())
		return towerMap[position];

	return NULL;
}