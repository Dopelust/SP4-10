#include "StageManager.h"
#include "../../../../Grid.h"
#include "Vector2.h"
#include <iostream>

using namespace std;

StageManager::StageManager() :
state(FREETIME),
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
	gold = 100;
	health = 20;

	currentStage = stageName;

	StageDatabase::Init(stageName.c_str());
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
		if (!enemies[i]->GetComponent<EnemyController>()->flying)
		{
			enemies[i]->GetComponent<PathFinder>()->UpdateMap(obstructionMap, enemies[i]->GetComponent<EnemyController>()->GetIndex(), endPoints);
		}
		else
		{
			enemies[i]->GetComponent<PathFinder>()->UpdateMap(obstacleMap, enemies[i]->GetComponent<EnemyController>()->GetIndex(), endPoints);
		}
	}
}

#include "EnemyController.h"
#include "StageGUI.h"

#include "../../../Scene.h"
#include "../../../../Tile.h"

void StageManager::Update(double dt)
{
	switch (state)
	{
	case FREETIME:
		
		if (gui->ButtonPress())
			StartWave();

		break;
	case WAVE:
		UpdateWave(dt);

		if (gui->ButtonPress())
		{
			state = PAUSED;
			Scene::scene->SetTimeScale(0);
		}

		break;
	case PAUSED:

		if (gui->ButtonPress())
		{
			state = WAVE;
			Scene::scene->SetTimeScale(1);
		}

		break;
	case WIN:
		break;
	case LOSE:
		break;
	}
}

#include "../../../Enemy/EnemyData.h"
#include "../../Entity.h"
#include "../Transform.h"
#include "TowerManager.h"

void StageManager::UpdateWave(double dt)
{	
	SpawnEnemies(dt);

	if (enemies.empty() && waveDone)
	{
		state = FREETIME;
		waveDone = false;
		waveQueue.pop();
		++currentWave;

		Save("Data//Save//stats.txt");
		tower->Save("Data//Save//save.txt");

		return;
	}
	
	for (int i = 0; i < enemies.size(); ++i)
	{
		EnemyController* ec = enemies[i]->GetComponent<EnemyController>();

		if (ec->pop)
		{
			// To Do : Add player money
			gold++;

			ec->pop = false;

			if (ec->split)
			{
				for (int j = 0; j < ec->GetData().split; ++j)
				{
					AddEnemy(enemies[i]->transform->GetPosition().GetVector2(), ec->GetIndex(), (ec->GetData().tier) - ec->popCount, enemies[i]->GetID());
				}
			}

			if (ec->done)
			{
				EntityFactory::Destroy(enemies[i]);
				enemies.erase(enemies.begin() + i);
				continue;
			}
		}
	}

	Fall(waveTimer, dt, 0);
}

bool StageManager::Hit()
{
	if (state == WAVE)
	{
		--health;

		if (health <= 0)
			state = LOSE;

		return true;
	}

	return false;
}

int StageManager::GetGold()
{
	return gold;
}

void StageManager::ReduceGold(int gold)
{
	this->gold -= gold;
}

void StageManager::CreateTileMap(vector<int>& obstructionIndex)
{
	obstructionMap.resize(NumberOfCellsX * NumberOfTilesX);
	for (unsigned i = 0; i < obstructionMap.size(); ++i)
	{
		obstructionMap[i].resize(NumberOfCellsY * NumberOfTilesY);
	}

	for (unsigned i = 0; i < obstructionMap.size(); ++i)
	{
		for (unsigned j = 0; j < obstructionMap[0].size(); ++j)
		{
			obstructionMap[i][j] = false;
		}
	}

	obstacleMap.resize(NumberOfCellsX * NumberOfTilesX);
	for (unsigned i = 0; i < obstacleMap.size(); ++i)
	{
		obstacleMap[i].resize(NumberOfCellsY * NumberOfTilesY);
	}

	for (unsigned i = 0; i < obstacleMap.size(); ++i)
	{
		for (unsigned j = 0; j < obstacleMap[0].size(); ++j)
		{
			obstacleMap[i][j] = false;
		}
	}

	// Init tileMap
	for (unsigned i = 0; i < NumberOfCellsX * NumberOfTilesX; ++i)
	{
		for (unsigned j = 0; j < NumberOfCellsY * NumberOfTilesY; ++j)
		{
			obstructionMap[i][j] = false;
			for (unsigned k = 0; k < obstructionIndex.size(); ++k)
			{
				if (Scene::scene->grid->GetTile(i, j)->index == obstructionIndex[k])
				{
					obstructionMap[i][j] = true;
					break;
				}
			}
		}
	}

	for (unsigned i = 0; i < NumberOfCellsX * NumberOfTilesX; ++i)
	{
		for (unsigned j = 0; j < NumberOfCellsY * NumberOfTilesY; ++j)
		{
			obstacleMap[i][j] = false;
			for (unsigned k = 0; k < obstructionIndex.size(); ++k)
			{
				if (Scene::scene->grid->GetTile(i, j)->index == obstructionIndex[k])
				{
					obstacleMap[i][j] = true;
					break;
				}
			}
		}
	}
}

bool StageManager::AddObstruction(int i, int j)
{
	obstructionMap[i][j] = true;

	for (auto& end : endPoints)
	{
		for (auto& start : spawnPoints)
		{
			if (!pathfind->UpdateMap(obstructionMap, end, start))
			{
				obstructionMap[i][j] = false;

				return false;
			}
		}
	}
	
	UpdatePathFinders();
	return true;
}

void StageManager::RemoveObstruction(int i, int j)
{
	obstructionMap[i][j] = false;
	UpdatePathFinders();
}

bool StageManager::CheckObstruction(int i, int j)
{
	return obstructionMap[i][j];
}

bool StageManager::InitWave()
{
	if (currentWave < GetData().GetNumStages())
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

		waveTimer = wave.waveData.GetWaveTime();
		spawnTimer = 1000;

		return true;
	}

	//Win
	return false;
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
		Entity* enemy = EntityFactory::GenerateEnemy(spawnPos.GetVector2(), 
			currentWave->waveData.tier[currentWave->spawnNo], 
			"Jellies", ("Jellies" + ToString(currentWave->waveData.tier[currentWave->spawnNo])).c_str(), 
			currentWave->waveData.flying[currentWave->spawnNo]);

		if (!enemy->GetComponent<EnemyController>()->flying)
		{
			enemy->AddComponent<PathFinder>()->UpdateMap(obstructionMap, spawnPoints[spawnPt], endPoints);
		}
		else
		{
			enemy->AddComponent<PathFinder>()->UpdateMap(obstacleMap, spawnPoints[spawnPt], endPoints);
		}

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

void StageManager::StartWave()
{
	if (InitWave())
		state = WAVE;
}

void StageManager::AddEnemy(const Vector2 &position, const Vector2 index, int tier, int parentID)
{
	Entity* enemy = EntityFactory::GenerateEnemy(position, tier, "Jellies", ("Jellies" + ToString(tier)).c_str(), false);
	enemy->AddComponent<PathFinder>()->UpdateMap(obstructionMap, index, endPoints);
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

#include "FileSystem.h"

bool StageManager::Load(const char * filepath)
{
	if (File.Exists(filepath))
	{
		vector<string>& lines = File.GetLines(filepath);

		for (auto& line : lines)
		{
			vector<string>& tokens = ParseLine(line, " ,");
			LoadStage(tokens[0]);
			currentWave = stoi(tokens[1]);
			health = stoi(tokens[2]);
			gold = stoi(tokens[3]);
		}

		return true;
	}

	return false;
}

void StageManager::Save(const char * filepath)
{
	ofstream& output = *File.BeginWriting(filepath);

	output << currentStage << ", ";
	output << currentWave << ", ";
	output << health << ", ";
	output << gold << ", ";

	File.EndWriting();

	gui->SetPopup("Saved Game");
}
