#include "Cell.h"

#include <algorithm>
using namespace::std;

Cell::Cell()
{
}

Cell::~Cell()
{
}

void Cell::Add(Entity* entity)
{
	entityList.push_back(entity);
}

void Cell::Remove(Entity * entity)
{
	auto it = find(entityList.begin(), entityList.end(), entity);

	if (it != entityList.end())
		entityList.erase(it);
}

void Cell::Reset()
{
	entityList.clear();
}

const vector<Entity*>& Cell::GetEntities()
{
	return entityList;
}

void Cell::Place(int i, int j, int index)
{
	tile[i][j].index = index;
}

void Cell::Draw(int i, int j)
{
	for (int x = 0; x < NumberOfTilesX; ++x)
	for (int y = 0; y < NumberOfTilesY; ++y)
	{
		tile[x][y].Draw(i + x, j + y);
	}
}

Tile& Cell::GetTile(int i, int j)
{
	return tile[i][j];
}