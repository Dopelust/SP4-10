#ifndef CELL_H
#define CELL_H

#include "GridInfo.h"
#include "Tile.h"

#include <vector>
using namespace::std;

struct Vector3;
class Entity;

class Cell
{
public:
	Cell();
	~Cell();

	void Place(int i, int j, int index);

	Tile& GetTile(int i, int j);
	Vector3 GetTileMinCoord(int i, int j);
	Vector3 GetTileMaxCoord(int i, int j);

	void Draw(int i, int j); 

private:
	Tile tile[NumberOfTilesX][NumberOfTilesY];
};

#endif
