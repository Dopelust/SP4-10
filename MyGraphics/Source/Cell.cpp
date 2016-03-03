#include "Cell.h"

#include <algorithm>
using namespace::std;

Cell::Cell()
{
}

Cell::~Cell()
{
}


void Cell::Place(int i, int j, int index)
{
	tile[i][j].index = index;
}

#include "Mtx44.h"

void Cell::Draw(int i, int j)
{
	for (int x = 0; x < NumberOfTilesX; ++x)
	for (int y = 0; y < NumberOfTilesY; ++y)
	{
		Mtx44& mtx = tile[x][y].GetTransformation(i + x, j + y);
		tile[x][y].Draw(mtx);

		if (tile[x][y].index != 2)
		{
			if (y + 1 < NumberOfTilesY && tile[x][y + 1].index == 2)
				Tile::DrawOcclusion(mtx, 7);
			if (y - 1 >= 0 && tile[x][y - 1].index == 2)
				Tile::DrawOcclusion(mtx, 1);
			if (x + 1 < NumberOfTilesX && tile[x + 1][y].index == 2)
				Tile::DrawOcclusion(mtx, 3);
			if (x - 1 >= 0 && tile[x - 1][y].index == 2)
				Tile::DrawOcclusion(mtx, 5);

			if (y + 1 < NumberOfTilesY && x + 1 < NumberOfTilesX && tile[x + 1][y + 1].index == 2)
				Tile::DrawOcclusion(mtx, 6);
			if (y + 1 < NumberOfTilesY && x - 1 >= 0 && tile[x - 1][y + 1].index == 2)
				Tile::DrawOcclusion(mtx, 8);
			if (y - 1 >= 0 && x + 1 < NumberOfTilesX && tile[x + 1][y - 1].index == 2)
				Tile::DrawOcclusion(mtx, 0);
			if (y - 1 >= 0 && x - 1 >= 0 && tile[x - 1][y - 1].index == 2)
				Tile::DrawOcclusion(mtx, 2);
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
	return Vector3(i * TileWidth, j * TileHeight); 
}
Vector3 Cell::GetTileMaxCoord(int i, int j)
{
	return GetTileMinCoord(i + 1, j + 1);
}