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
spawnNo(0),
countNo(0),
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

	CreatePathFinders();

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
}

StageData& StageManager::GetData()
{
	return StageDatabase::GetData(currentStage);
}


void StageManager::CreatePathFinders()
{
	/*for (int i = 0; i < spawnPoints.size(); ++i)
	{
		Entity *entity = EntityFactory::GeneratePathFinder();
		entity->GetComponent<PathFinder>()->UpdateMap(tileMap);
		entity->GetComponent<PathFinder>()->SetStart(spawnPoints[i]);
		pathFinders.push_back(entity);
	}*/
}

#include "EnemyController.h"

void StageManager::UpdatePathFinders()
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->GetComponent<PathFinder>()->SetStart(enemies[i]->GetComponent<EnemyController>()->indexPos);
		enemies[i]->GetComponent<PathFinder>()->UpdateMap(tileMap, endPoints);
		enemies[i]->GetComponent<EnemyController>()->UpdatePath();
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
		InitWave();
		UpdatePathFinders();
		freeTimer = 0;
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
		++currentWave;
		if (currentWave >= maxWave)
		{
			currentWave = 0;
		}
		waveDone = false;
		return;
	}
	
	for (unsigned i = 0; i < enemies.size(); ++i)
	{
		EnemyController* ec = enemies[i]->GetComponent<EnemyController>();

		if (ec->done)
		{
			if (ec->pop)
			{
				for (int j = 0; j < ec->GetData().split; ++j)
				{
					AddEnemy(enemies[i]->transform->GetPosition().GetVector2(), ec->indexPos, (ec->GetData().tier) - 1, ec->steps, enemies[i]->GetID());
				}
			}

			EntityFactory::Destroy(enemies[i]);
			enemies.erase(enemies.begin() + i);
			--i;
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
		pathfind->SetStart(end);

		if (!pathfind->UpdateMap(tileMap, spawnPoints))
		{
			tileMap[i][j] = false;
			return false;
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

void StageManager::InitWave()
{
	for (int i = 0; i < GetData().stageData[currentWave].count.size(); ++i)
	{
		for (int j = 0; j < GetData().stageData[currentWave].count[i]; ++j)
		{
			spawnQueue.push(GetData().stageData[currentWave]);
		}
	}

	countNo = 0;
	spawnNo = 0;
	spawnTimer = 0;
}

#include "../../../AStar/AStar.h"

void StageManager::SpawnEnemies(double dt)
{
	spawnTimer += (float)dt;

	if (spawnQueue.empty())
	{
		waveDone = true;
	}
	else if (spawnTimer > spawnQueue.front().delay[spawnNo])
	{
		int spawnPt = rand() % spawnPoints.size();
		Vector3 spawnPos = Scene::scene->grid->GetPosition(spawnPoints[spawnPt]);
		Entity* enemy = EntityFactory::GenerateEnemy(spawnPos.GetVector2(), spawnQueue.front().tier[spawnNo]);
		enemy->AddComponent<PathFinder>()->SetStart(spawnPoints[spawnPt]);
		enemy->GetComponent<PathFinder>()->UpdateMap(tileMap, endPoints);
		enemy->GetComponent<EnemyController>()->UpdatePath();

		enemies.push_back(enemy);

		++countNo;

		if (countNo >= spawnQueue.front().count[spawnNo])
		{
			countNo = 0;
			++spawnNo;
		}

		spawnQueue.pop();
		spawnTimer = 0;
	}
}

void StageManager::AddEnemy(const Vector2 &position, const Vector2 index, int tier, int step, int parentID)
{
	Entity* enemy = EntityFactory::GenerateEnemy(position, tier);
	enemy->AddComponent<PathFinder>()->SetStart(index);
	enemy->GetComponent<PathFinder>()->UpdateMap(tileMap, endPoints);
	enemy->GetComponent<EnemyController>()->UpdatePath();
	enemy->GetComponent<EnemyController>()->steps = step;
	enemy->GetComponent<EnemyController>()->parentID = parentID;

	enemies.push_back(enemy);
}

string StageManager::GetStageName()
{
	return currentStage;
}