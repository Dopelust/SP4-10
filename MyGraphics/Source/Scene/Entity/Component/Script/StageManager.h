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

class TowerManager;
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

struct Achievement
{
	Achievement() :
	gamesPlayed(0),
	gamesWon(0),
	towersPlaced(0),
	towersUpgraded(0),
	towersMaxUpgraded(0),
	enemiesPopped(0),
	enemiesLeaked(0),
	wavesCompleted(0)
	{
	}

	~Achievement()
	{
	}

	int gamesPlayed;
	int gamesWon;
	int towersPlaced;
	int towersUpgraded;
	int towersMaxUpgraded;
	int enemiesPopped;
	int enemiesLeaked;
	int wavesCompleted;
};

class StageManager :
	public Component
{
public:
	StageManager();
	~StageManager();

	TowerManager* tower;
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

	bool Load(const char* filepath);
	void Save(const char* filepath);
	bool LoadAchievement(const char* filepath);
	void SaveAchievement(const char* filepath);

	Achievement achievement;

	enum StageState
	{
		FREETIME,
		WAVE,
		PAUSED,
		WIN,
		LOSE,
		MAX_STATE,
	};
	StageState state;

	bool Hit();
	int GetGold();
	void ReduceGold(int gold);
	void AddGold(int gold);

private:
	friend StageGUI;

	int gold;
	int health;

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

	float waveTimer;
	float spawnTimer;

	queue<StageWave> waveQueue;

	vector<vector<bool>> obstructionMap;
	vector<vector<bool>> obstacleMap;
};

#endif