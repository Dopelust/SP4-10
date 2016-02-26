#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "../Component.h"
#include "../../../Stage/StageData.h"

#include <string>
#include <vector>
#include <queue>

using std::string;
using std::vector;
using std::queue;

struct Vector2;

class PathFinder;

class StageGUI;
class Grid;
class GridInfo;
class Entity;
class StageData;

struct StageWave
{
	StageWave() :
	countNo(0),
	spawnNo(0)
	{

	}

	~StageWave()
	{
		while (!spawnQueue.empty())
		{
			spawnQueue.pop();
		}
	}

	queue<int> spawnQueue;
	WaveData waveData;
	// Count per batch
	int countNo;
	// Spawn batches
	int spawnNo;
};

class StageManager :
	public Component
{
public:
	StageManager();
	~StageManager();

	StageGUI* gui;

	void Init(Entity* ent);
	void LateInit(Grid* grid, vector<int>& obstructionIndex);
	// Load Stage Data
	void LoadStage(string stageName);
	void Update(double dt);

	bool AddObstruction(int i, int j);
	void RemoveObstruction(int i, int j);
	bool CheckObstruction(int i, int j);
	void AddEnemy(const Vector2 &position, const Vector2 index, int tier, int parentID);

	string GetStageName();

	vector<Entity*>& Enemies();
	vector<Vector2>& EndPoints();

private:
	friend StageGUI;

	void CreateTileMap(vector<int>& obstructionIndex);
	void UpdatePathFinders();
	void UpdateWave(double dt);
	bool InitWave();
	void SpawnEnemies(double dt);

	void StartWave();

	StageData& GetData();

	PathFinder* pathfind;
	Entity *owner;

	string currentStage;

	vector<Vector2> spawnPoints;
	vector<Vector2> endPoints;
	vector<Entity*> enemies;

	int maxWave;
	int currentWave;
	bool waveDone;

	enum StageState
	{
		FREETIME,
		WAVE,
		MAX_STATE,
	};

	StageState state;

	float waveTimer;
	float spawnTimer;

	queue<StageWave> waveQueue;

	vector<vector<bool>> obstructionMap;
	vector<vector<bool>> obstacleMap;
};

#endif