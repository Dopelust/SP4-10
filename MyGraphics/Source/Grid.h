#ifndef GRID_H
#define GRID_H

#include "GridInfo.h"

struct Vector3;
struct Vector2;

#include <vector>
using namespace::std;

class Tile;
class Scene;
class Cell;
class Entity;
class Grid
{
public:
	virtual bool Save(const char* filepath);
	virtual bool Load(const char* filepath);

	Grid(Scene* owner);
	virtual ~Grid();
	
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ResolveCollisions(Entity* ent);
	Vector3 GetIndex(const Vector3& position);

	vector<Cell*> GetCellsInRange(Entity* entity, float range);
	vector<Entity*> GetEntitiesInRange(Entity* entity, float range);

	Cell* GetCell(int x, int y);
	Tile* GetTile(int x, int y);

	vector<Vector2> GetTilesWithIndex(int index);
	Vector3 GetPosition(const Vector2& index);

protected:
	Scene* owner;
	Cell* cell[NumberOfCellsX][NumberOfCellsY];

private:
	void PopulateCells(Entity* ent);
};

#endif
