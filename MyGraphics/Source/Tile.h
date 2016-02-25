#ifndef TILE_H
#define TILE_H

#include "GridInfo.h"

#include <vector>
using namespace::std;

class Tile
{
public:
	Tile();
	~Tile();

	int index;
	void Draw(int i, int j); 

	static void DrawOcclusion(int i, int j, int orientation);
};

#endif
