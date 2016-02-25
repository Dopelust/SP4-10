#include "StageManager.h"
#include "../../../../Grid.h"
#include "Vector2.h"
#include <iostream>

using namespace std;

StageManager::StageManager() :
freeTimer(0),
state(FREETIME),
freeTime(0),
waveTimer(0),
spawnTimer(0),
owner(NULL),
currentWave(0),
waveDone(false)
{
}

StageManager::~StageManager()
{

}

#include "../../Entity.h"
#include "../../Component/Script/PathFinder.h"
#include "../../EntityFactory.h"

void StageManager::Init(Entity* ent)
{
	this->owner = ent;
	pathfind = ent->GetComponent<PathFinder>();
}

#include "../../EntityFactory.h"

void StageManager::LateInit(Grid* grid, vector<int>& obstructionIndex)
{
	spawnPoints = grid->GetTilesWithIndex(3);
	endPoints = grid->GetTilesWithIndex(4);

	CreateTileMap(obstructionIndex);

	UpdatePathFinders();
}

#include <iostream>
#include <fstream>
#include <istream>

using namespace std;
#include "Utility.h"

#include "../../../Stage/StageDatabase.h"

void StageManager::LoadStage(string stageName)
{
	currentStage = stageName;
	maxWave = GetData().stageData.size();

	//InitAllWave();
}

StageData& StageManager::GetData()
{
	return StageDatabase::GetData(currentStage);
}

#include "EnemyController.h"

void StageManager::UpdatePathFinders()
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->GetComponent<PathFinder>()->UpdateMap(tileMap, enemies[i]->GetComponent<EnemyController>()->GetIndex(), endPoints);
	}
}

#include "EnemyController.h"

void StageManager::Update(double dt)
{
	switch (state)
	{
	case FREETIME:
		UpdateFreeTime(dt);
		break;
	case WAVE:
		UpdateWave(dt);
		break;
	}
}

void StageManager::UpdateFreeTime(double dt)
{
	freeTimer += (float)dt;
	if (freeTimer > freeTime)
	{
		state = WAVE;
		UpdatePathFinders();
		freeTimer = 0;
		InitWave();
	}
}

#include "../../../Enemy/EnemyData.h"
#include "../../Entity.h"
#include "../Transform.h"

void StageManager::UpdateWave(double dt)
{	
	SpawnEnemies(dt);

	if (enemies.empty() && waveDone)
	{
		state = FREETIME;
		waveDone = false;
		waveQueue.pop();
		return;
	}
	
	for (unsigned i = 0; i < enemies.size(); ++i)
	{
		EnemyController* ec = enemies[i]->GetComponent<EnemyController>();

		if (ec->pop)
		{
			// To Do : Add player money

			ec->pop = false;

			if (ec->split)
			{
				for (int j = 0; j < ec->GetData().split; ++j)
				{
					if (ec->GetTier() - ec->popCount > 0)
						AddEnemy(enemies[i]->transform->GetPosition().GetVector2(), ec->GetIndex(), (ec->GetData().tier) - ec->popCount, enemies[i]->GetID());
				}
			}

			if (ec->done)
			{
				EntityFactory::Destroy(enemies[i]);
				enemies.erase(enemies.begin() + i);
				--i;
				continue;
			}
		}
	}
}

#include "../../../Scene.h"
#include "../../../../Tile.h"

void StageManager::CreateTileMap(vector<int>& obstructionIndex)
{
	tileMap.resize(NumberOfCellsX * NumberOfTilesX);
	for (unsigned i = 0; i < tileMap.size(); ++i)
	{
		tileMap[i].resize(NumberOfCellsY * NumberOfTilesY);
	}

	for (unsigned i = 0; i < tileMap.size(); ++i)
	{
		for (unsigned j = 0; j < tileMap[0].size(); ++j)
		{
			tileMap[i][j] = false;
		}
	}

	// Init tileMap
	for (unsigned i = 0; i < NumberOfCellsX * NumberOfTilesX; ++i)
	{
		for (unsigned j = 0; j < NumberOfCellsY * NumberOfTilesY; ++j)
		{
			tileMap[i][j] = false;
			for (unsigned k = 0; k < obstructionIndex.size(); ++k)
			{
				if (Scene::scene->grid->GetTile(i, j)->index == obstructionIndex[k])
				{
					tileMap[i][j] = true;
					break;
				}
			}
		}
	}
}

bool StageManager::AddObstruction(int i, int j)
{
	tileMap[i][j] = true;

	for (auto& end : endPoints)
	{
		for (auto& start : spawnPoints)
		{
			if (!pathfind->UpdateMap(tileMap, end, start))
			{
				tileMap[i][j] = false;

				return false;
			}
		}
	}
	
	UpdatePathFinders();
	return true;
}

void StageManager::RemoveObstruction(int i, int j)
{
	tileMap[i][j] = false;
	UpdatePathFinders();
}

bool StageManager::CheckObstruction(int i, int j)
{
	return tileMap[i][j];
}

void StageManager::InitAllWave()
{
	for (int k = 0; k < GetData().stageData.size(); ++k)
	{
		StageWave wave;
		wave.waveData = GetData().stageData[k];
		for (int i = 0; i < GetData().stageData[k].count.size(); ++i)
		{
			for (int j = 0; j < GetData().stageData[k].count[i]; ++j)
			{
				wave.spawnQueue.push(j);
			}
		}
		waveQueue.push(wave);
	}

	spawnTimer = 0;
}

void StageManager::InitWave()
{
	StageWave wave;
	wave.waveData = GetData().stageData[currentWave];
	for (int i = 0; i < GetData().stageData[currentWave].count.size(); ++i)
	{
		for (int j = 0; j < GetData().stageData[currentWave].count[i]; ++j)
		{
			wave.spawnQueue.push(j);
		}
	}
	waveQueue.push(wave);

	++currentWave;
}

#include "../../../AStar/AStar.h"

void StageManager::SpawnEnemies(double dt)
{
	spawnTimer += (float)dt;

	StageWave *currentWave;
	currentWave = &waveQueue.front();

	if (currentWave->spawnQueue.empty())
	{
		waveDone = true;
	}
	else if (spawnTimer > currentWave->waveData.delay[currentWave->spawnNo])
	{
		int spawnPt = rand() % spawnPoints.size();
		Vector3 spawnPos = Scene::scene->grid->GetPosition(spawnPoints[spawnPt]);
		Entity* enemy = EntityFactory::GenerateEnemy(spawnPos.GetVector2(), currentWave->waveData.tier[currentWave->spawnNo], "Jellies", ("Jellies" + ToString(currentWave->waveData.tier[currentWave->spawnNo])).c_str());

		enemy->AddComponent<PathFinder>()->UpdateMap(tileMap, spawnPoints[spawnPt], endPoints);

		enemies.push_back(enemy);

		++currentWave->countNo;
	
		if (currentWave->countNo >= currentWave->waveData.count[currentWave->spawnNo])
		{
			currentWave->countNo = 0;
			++currentWave->spawnNo;
		}

		currentWave->spawnQueue.pop();
		spawnTimer = 0;
	}
}

void StageManager::AddEnemy(const Vector2 &position, const Vector2 index, int tier, int parentID)
{
	Entity* enemy = EntityFactory::GenerateEnemy(position, tier, "Jellies", ("Jellies" + ToString(tier)).c_str());
	enemy->AddComponent<PathFinder>()->UpdateMap(tileMap, index, endPoints);
	enemy->GetComponent<EnemyController>()->parentID = parentID;

	enemies.push_back(enemy);
}

string StageManager::GetStageName()
{
	return currentStage;
}

vector<Entity*>& StageManager::Enemies()
{
	return enemies;
}

vector<Vector2>& StageManager::EndPoints()
{
	return endPoints;
}