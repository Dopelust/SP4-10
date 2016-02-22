#include "StageManager.h"
#include "../../../../Grid.h"
#include "Vector2.h"
#include <iostream>

using namespace std;

StageManager::StageManager() :
freeTimer(0),
state(FREETIME),
freeTime(0),
waveTimer(0)
{
}

StageManager::~StageManager()
{

}

void StageManager::Init(Entity* ent)
{
	this->owner = ent;
}

#include "../../EntityFactory.h"

void StageManager::LateInit(string stageName, Grid* grid, vector<int>& obstructionIndex)
{
	this->stageName = stageName;

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

void StageManager::LoadStage(const char * stageFilePath)
{
	// To Do: Load enemy spawn pattern, free time, player base health
	/*ifstream stageDataFile(ToString("Data//Prefab//Tower//", stageFilePath, ".txt").c_str());

	string line;

	if (stageDataFile.is_open())
	{
		while (!stageDataFile.eof())
		{
			getline(stageDataFile, line, ' ');

			if (!(line.size() > 2 && line[0] == line[1] == '/'))
			{
				getline(stageDataFile, name, '\n');
			}
		}

		towerDataFile.close();
	}*/
}

#include "../../Entity.h"
#include "../../Component/Script/PathFinder.h"

void StageManager::CreatePathFinders()
{
	for (int i = 0; i < spawnPoints.size(); ++i)
	{
		Entity *entity = EntityFactory::GeneratePathFinder();
		entity->GetComponent<PathFinder>()->UpdateMap(tileMap);
		entity->GetComponent<PathFinder>()->SetStart(spawnPoints[i]);
		pathFinders.push_back(entity);
	}
}

void StageManager::UpdatePathFinders()
{
	for (int i = 0; i < pathFinders.size(); ++i)
	{
		pathFinders[i]->GetComponent<PathFinder>()->UpdateMap(tileMap);
	}

	for (int i = 0; i < pathFinders.size(); ++i)
	{
		Vector2 shortestEnd;
		int shortestPathLength = 999;

		Entity* ent = pathFinders[i];

		for (int j = 0; j < endPoints.size(); ++j)
		{
			ent->GetComponent<PathFinder>()->SetEnd(endPoints[j]);
			if (ent->GetComponent<PathFinder>()->CalculatePath())
			{
				int length = ent->GetComponent<PathFinder>()->GetPathLength();

				if (length < shortestPathLength)
				{
					shortestPathLength = length;
					shortestEnd = endPoints[j];
				}
			}
		}

		ent->GetComponent<PathFinder>()->SetEnd(shortestEnd);
		ent->GetComponent<PathFinder>()->CalculatePath();
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
		SpawnEnemies();
		freeTimer = 0;
	}
}

void StageManager::UpdateWave(double dt)
{	
	if (enemies.empty())
	{
		state = FREETIME;
		return;
	}
	
	for (unsigned i = 0; i < enemies.size(); ++i)
	{
		if (enemies[i]->GetComponent<EnemyController>()->done)
		{
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

void StageManager::AddObstruction(int i, int j)
{
	tileMap[i][j] = true;
}

void StageManager::RemoveObstruction(int i, int j)
{
	tileMap[i][j] = false;
}

bool StageManager::CheckObstruction(int i, int j)
{
	return tileMap[i][j];
}

#include "../../../AStar/AStar.h"

void StageManager::SpawnEnemies()
{
	// To Do: Monster spawning from text file
	for (int i = 0; i < spawnPoints.size(); ++i)
	{
		Vector3 spawnPos = Scene::scene->grid->GetPosition(spawnPoints[i]);
		Entity* enemy = EntityFactory::GenerateEnemy(spawnPos.GetVector2(), 1);
		enemy->GetComponent<EnemyController>()->SetNode(pathFinders[i]->GetComponent<PathFinder>()->GetStart());

		enemies.push_back(enemy);
	}
}

string StageManager::GetStageName()
{
	return stageName;
}