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

#include "../../../../SoundEngine.h"

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
	if (CanPurchase(type))
	{
		Unselect();

		ShowIndicator(true);
		ShowInfo(type);

		this->type = type;
	}
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
	Vector3& index = Scene::scene->grid->GetIndex(position);

	if (stage->AddObstruction((int)index.x, (int)index.y))
	{
		towerMap[position] = EntityFactory::GenerateTower(position.GetVector2(), type);
		stage->ReduceGold(TowerDatabase::GetData(type.c_str())[0].cost);

		Audio.Play2D(Audio.GetSoundPack("build"), 0.5f);

		type = "";
		HideInfo();
		HideIndicator();

		return true;
	}

	return false;
	
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
				graphic->color.Set(0, 1, 0, 0.5f); //Change Indicator To Green

				if (Input.IsMousePress(0)) //If Left Click
				{
					PlaceTower(); //Place Tower
				}
			}
			else //If Invalid Spot
			{
				graphic->color.Set(1, 0, 0, 0.5f); //Change Indicator To Red
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
	TowerController* t = tower->GetComponent<TowerController>();

	gui->ShowInfo(t->type.c_str(), t->upgrade);
	range->transform->SetSize((float)(t->GetRange() * 2), (float)(t->GetRange() * 2));
}

void TowerManager::ShowInfo(string type)
{
	TowerData* data = &TowerDatabase::GetData(type.c_str())[0];

	gui->ShowInfo(type.c_str(), 0);
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
		selection->GetComponent<Graphic2D>()->color.Set(1, 1, 1, 1);
		gui->DisableUpgrades();
		gui->DisableSale();

		HideIndicator();
		HideInfo();

		this->selection = NULL;
	}
}

void TowerManager::Select(Entity * tower)
{
	this->selection = tower;

	gui->EnableSale();

	if (tower->GetComponent<TowerController>()->IsMaxUpgrade())
		gui->DisableUpgrades();
	else
		gui->EnableUpgrades();

	tower->GetComponent<Graphic2D>()->color.Set(2, 2, 2, 1);

	ShowIndicator(false);
	ShowInfo(tower);
}

void TowerManager::UpgradeTower()
{
	if (CanUpgrade())
	{
		TowerController* tower = selection->GetComponent<TowerController>();

		stage->ReduceGold(tower->GetUpgradePrice());
		tower->Upgrade();
		ShowInfo(selection);
		++stage->achievement.towersUpgraded;

		if (tower->IsMaxUpgrade())
		{
			gui->DisableUpgrades();
			++stage->achievement.towersMaxUpgraded;
		}

		Audio.Play2D(Audio.GetSoundPack("build"), 0.5f);
	}
}

void TowerManager::SellTower()
{
	if (selection)
	{
		stage->AddGold(selection->GetComponent<TowerController>()->GetSellPrice());

		Vector3& index = Scene::scene->grid->GetIndex(selection->transform->GetPosition());
		stage->RemoveObstruction(index.x, index.y);

		EntityFactory::Destroy(selection);
		towerMap.erase(selection->transform->GetPosition());

		Unselect();

		Audio.Play2D(Audio.GetSoundPack("sell"), 0.5f);
	}
}

Entity*  TowerManager::GetTower(const Vector3& position)
{
	if (towerMap.find(position) != towerMap.end())
		return towerMap[position];

	return NULL;
}

#include "FileSystem.h"
#include "Utility.h"

void TowerManager::Load(const char * filepath)
{
	vector<string>& lines = File.GetLines(filepath);

	for (auto& line : lines)
	{
		vector<string>& tokens = ParseLine(line, " ,");

		Vector3 position(stoi(tokens[0]), stoi(tokens[1]), stoi(tokens[2]));
		Vector3& index = Scene::scene->grid->GetIndex(position);

		if (stage->AddObstruction((int)index.x, (int)index.y))
		{
			towerMap[position] = EntityFactory::GenerateTower(position.GetVector2(), tokens[3]);
			towerMap[position]->GetComponent<TowerController>()->SetUpgrade(stoi(tokens[4]));
		}
	}
}

void TowerManager::Save(const char * filepath)
{
	ofstream& output = *File.BeginWriting(filepath);

	for (auto& tower : towerMap)
	{
		TowerController* t = tower.second->GetComponent<TowerController>();

		output << tower.first << " " << t->type << " " << t->upgrade << endl;
	}

	File.EndWriting();
}

bool TowerManager::CanPurchase(const char * type)
{
	return stage->GetGold() >= TowerDatabase::GetData(type)[0].cost;
}

bool TowerManager::CanUpgrade()
{
	if (selection)
	{
		TowerController* tower = selection->GetComponent<TowerController>();

		if (!tower->IsMaxUpgrade() && stage->GetGold() >= tower->GetUpgradePrice())
			return true;
	}

	return false;
}
