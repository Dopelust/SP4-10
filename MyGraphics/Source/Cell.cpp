#include "Cell.h"

#include <algorithm>
using namespace::std;

Cell::Cell(int x, int y) : x(x), y(y)
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

		if (tile[x][y].index != 2)
		{
			if (y + 1 < NumberOfTilesY && tile[x][y + 1].index == 2)
				Tile::DrawOcclusion(i + x, j + y, 7);
			if (y - 1 >= 0 && tile[x][y - 1].index == 2)
				Tile::DrawOcclusion(i + x, j + y, 1);
			if (x + 1 < NumberOfTilesX && tile[x + 1][y].index == 2)
				Tile::DrawOcclusion(i + x, j + y, 3);
			if (x - 1 >= 0 && tile[x - 1][y].index == 2)
				Tile::DrawOcclusion(i + x, j + y, 5);

			if (y + 1 < NumberOfTilesY && x + 1 < NumberOfTilesX && tile[x + 1][y + 1].index == 2)
				Tile::DrawOcclusion(i + x, j + y, 6);
			if (y + 1 < NumberOfTilesY && x - 1 >= 0 && tile[x - 1][y + 1].index == 2)
				Tile::DrawOcclusion(i + x, j + y, 8);
			if (y - 1 >= 0 && x + 1 < NumberOfTilesX && tile[x + 1][y - 1].index == 2)
				Tile::DrawOcclusion(i + x, j + y, 0);
			if (y - 1 >= 0 && x - 1 >= 0 && tile[x - 1][y - 1].index == 2)
				Tile::DrawOcclusion(i + x, j + y, 2);
		}
	}
}

Tile& Cell::GetTile(int i, int j)
{
	return tile[i][j];
}

#include "Vector3.h"

Vector3 Cell::GetTileMinCoord(int i, int j)
{
	return Vector3(x * CellWidth + i * TileWidth, y * CellHeight + j * TileHeight); 
}
Vector3 Cell::GetTileMaxCoord(int i, int j)
{
	return GetTileMinCoord(i + 1, j + 1);
}