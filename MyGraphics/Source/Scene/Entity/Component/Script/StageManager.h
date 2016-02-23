#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "../Component.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Vector2;

// Stage Manager
// Spawns enemy and manages progression
class Grid;
class GridInfo;
class Entity;

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
	void LateInit(string stageName, Grid* grid, vector<int>& obstructionIndex);
	// Load Stage Data
	void LoadStage(const char * stageFilePath);
	void Update(double dt);

	void AddObstruction(int i, int j);
	void RemoveObstruction(int i, int j);
	bool CheckObstruction(int i, int j);
	void SpawnEnemies();
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

	Entity *owner;
	string stageName;

	int noWaves;
	StageState state;
	const float freeTime;
	float freeTimer;
	float waveTimer;

	vector<vector<bool>> tileMap;
};

#endif