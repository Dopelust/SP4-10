#ifndef TILE_H
#define TILE_H

#include "GridInfo.h"

#include <vector>
using namespace::std;

class Mtx44;

class Tile
{
public:
	Tile();
	~Tile();

	int index;

	static Mtx44 GetTransformation(int i, int j);
	static void DrawOcclusion(const Mtx44& mtx, int orientation);

	void Draw(const Mtx44& mtx);
};

#endif
