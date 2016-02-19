#ifndef CELL_H
#define CELL_H

#include "GridInfo.h"
#include "Tile.h"

#include <vector>
using namespace::std;

class Entity;
class Cell
{
public:
	Cell();
	~Cell();

	void Add(Entity* entity);
	void Remove(Entity* entity);

	void Reset();
	const vector<Entity*>& GetEntities();

	void Place(int i, int j, int index);
	Tile& GetTile(int i, int j);
	void Draw(int i, int j); 
private:
	vector<Entity*> entityList;
	Tile tile[NumberOfTilesX][NumberOfTilesY];
};

#endif
