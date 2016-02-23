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

// Stage Manager
// Spawns enemy and manages progression
class Grid;
class GridInfo;
class Entity;
class StageData;

enum StageState
{
	FREETIME,
	WAVE,
	MAX_STATE,
};

class StageManager :
	public Component
{
public:
	StageManager();
	~StageManager();

	void Init(Entity* ent);
	void LateInit(Grid* grid, vector<int>& obstructionIndex);
	// Load Stage Data
	void LoadStage(string stageName);
	void Update(double dt);

	bool AddObstruction(int i, int j);
	void RemoveObstruction(int i, int j);
	bool CheckObstruction(int i, int j);
	void SpawnEnemies(double dt);
	void AddEnemy(const Vector2 &position, const Vector2 index, int tier, int step, int parentID);

	string GetStageName();

	vector<Vector2> spawnPoints;
	vector<Vector2> endPoints;
	//vector<Entity*> pathFinders;
	vector<Entity*> enemies;

private:
	void CreateTileMap(vector<int>& obstructionIndex);
	void UpdatePathFinders();
	void CreatePathFinders();
	void UpdateFreeTime(double dt);
	void UpdateWave(double dt);
	void InitWave();

	StageData& GetData();

	PathFinder* pathfind;
	Entity *owner;

	string currentStage;

	int maxWave;
	int currentWave;
	bool waveDone;

	StageState state;
	const float freeTime;
	float freeTimer;
	float waveTimer;
	float spawnTimer;

	queue<WaveData> spawnQueue;
	int countNo;
	int spawnNo;

	vector<vector<bool>> tileMap;
};

#endif