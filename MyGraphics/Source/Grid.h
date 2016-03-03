#ifndef GRID_H
#define GRID_H

#include "GridInfo.h"

struct Vector3;
struct Vector2;

#include <vector>
using namespace::std;

class Partition;
class Tile;
class Scene;
class Cell;
class Entity;
class Grid
{
public:
	virtual bool Save(const char* filepath);
	virtual bool Load(const char* filepath);

	void Reset();

	Grid(Scene* owner);
	virtual ~Grid();
	
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ResolveCollisions(Entity* ent);
	static Vector3 GetIndex(const Vector3& position);

	vector<Partition*> GetCellsInRange(Entity* entity, float range);
	vector<Entity*> GetEntitiesInRange(Entity* entity, float range);

	Partition* GetPartition(int x, int y);
	Tile* GetTile(int x, int y);

	vector<Vector2> GetTilesWithIndex(int index);
	static Vector3 GetPosition(const Vector2& index);

protected:
	Scene* owner;
	Cell* cell;
	Partition* part[NumberOfPartitionsX][NumberOfPartitionsY];

private:
	void PopulateCells(Entity* ent);
};

#endif
